<?php
/*

   SIMPL tclSurrogate Protocol Implementation for PHP

   Copyright (c)2011 Dimitri Tarassenko 

   This software is in the public domain.
   Permission to use, copy, modify, and distribute this software and its
   documentation for any purpose and without fee is hereby granted,
   without any conditions or restrictions.
   This software is provided "as is" without express or implied warranty.
   
   If you discover a bug or add an enhancement contact us on the
   SIMPL project mailing list.

*/

/**
 * Exceptions that may be thrown by SIMPLSender
 */
class SIMPLException extends Exception {}
class SIMPLConnectionError extends SIMPLException {}
class SIMPLCommunicationError extends SIMPLException {}
class SIMPLNameNotFound extends SIMPLException {}

/**
 * Implements tclSurrogate protocol for SIMPL
 * @author Dimitri Tarassenko <mitka@mitka.us>
 */
class SIMPLSender {
   
   const NAME_ATTACH =     0;
   const NAME_DETACH =     1;
   const NAME_LOCATE =     2;
   const SEND_IT =         3;
   const REPLY_IT =        4;
   const RELAY_IT =        5;
   const IS_LOGGER_UP =    6;
   const LOGIT =           7;
   const SEND_NO_REPLY =   8;
   const ACK =             9;
   const MIN_TOKEN =       self::NAME_ATTACH;
   const MAX_TOKEN =       self::ACK;
   
   const DEFAULT_PORT =    8000;          // default TCP port used by tclSurrogate receivers
   const DEFAULT_SENDER_NAME = "PHP";    
   const DEFAULT_CONNECT_TIMEOUT = 10;    // seconds
   const SOCKET_TIMEOUT = 10;             // seconds
   
   const DEBUG = false;
   
   private $receiver_id = null;
   private $socket = null;
   
   /**
    * Connects to the tclSurrogate SIMPL Receiver through a socket. Sockets are specified
    * as per http://us3.php.net/manual/en/function.stream-socket-client.php, i.e. for a TCP
    * connection: "tcp://<hostname/IP>:<port_number>".
    *  
    * @param string $socket socket definition
    * @param string $receiver_name receiver name to locate
    * @param string $sender_name optional name of the sender (us)
    * @param float $connect_timeout optional connection timeout in seconds
    */
   public function __construct( $remote_socket, $receiver_name, 
      $sender_name = self::DEFAULT_SENDER_NAME, $connect_timeout = self::DEFAULT_CONNECT_TIMEOUT ) 
   {      
      // Open the socket
      $this->socket = stream_socket_client( $remote_socket, $errno, $errstr, $connect_timeout );
      if ($errno || !$this->socket) {
         throw new SIMPLConnectionError("Error $errno: $errstr while connecting to $remote_socket");
      }
      stream_set_timeout($this->socket, self::SOCKET_TIMEOUT);
      
      // Attach our name
      $this->name_attach($sender_name);
      
      // Find the receiver
      $this->receiver_id = $this->name_locate($receiver_name);
   }
   
   /**
    * Destructor
    */
   public function __destruct()
   {
      // Shutdown the socket
      $this->name_detach();
      if ($this->socket) stream_socket_shutdown( $this->socket,STREAM_SHUT_RDWR );
   }
   
   /**
    * View any string as a hexdump.
    *
    * This is most commonly used to view binary data from streams
    * or sockets while debugging, but can be used to view any string
    * with non-viewable characters.
    *
    * @version     1.3.2
    * @author      Aidan Lister <aidan@php.net>
    * @author      Peter Waller <iridum@php.net>
    * @link        http://aidanlister.com/2004/04/viewing-binary-data-as-a-hexdump-in-php/
    * @param       string  $data        The string to be dumped
    * @param       bool    $htmloutput  Set to false for non-HTML output
    * @param       bool    $uppercase   Set to true for uppercase hex
    * @param       bool    $return      Set to true to return the dump
    */
   function hexdump ($data, $htmloutput = false, $uppercase = false, $return = true)
   {
       // Init
       $hexi   = '';
       $ascii  = '';
       $dump   = ($htmloutput === true) ? '<pre>' : '';
       $offset = 0;
       $len    = strlen($data);
   
       // Upper or lower case hexadecimal
       $x = ($uppercase === false) ? 'x' : 'X';
   
       // Iterate string
       for ($i = $j = 0; $i < $len; $i++)
       {
           // Convert to hexidecimal
           $hexi .= sprintf("%02$x ", ord($data[$i]));
   
           // Replace non-viewable bytes with '.'
           if (ord($data[$i]) >= 32) {
               $ascii .= ($htmloutput === true) ?
                               htmlentities($data[$i]) :
                               $data[$i];
           } else {
               $ascii .= '.';
           }
   
           // Add extra column spacing
           if ($j === 7) {
               $hexi  .= ' ';
               $ascii .= ' ';
           }
   
           // Add row
           if (++$j === 16 || $i === $len - 1) {
               // Join the hexi / ascii output
               $dump .= sprintf("%04$x  %-49s  %s", $offset, $hexi, $ascii);
   
               // Reset vars
               $hexi   = $ascii = '';
               $offset += 16;
               $j      = 0;
   
               // Add newline
               if ($i !== $len - 1) {
                   $dump .= "\n";
               }
           }
       }
   
       // Finish dump
       $dump .= $htmloutput === true ?
                   '</pre>' :
                   '';
       $dump .= "\n";
   
       // Output method
       if ($return === false) {
           echo $dump;
       } else {
           return $dump;
       }
   }
      
   
   /**
    * Sends the message to the socket, then waits for the response and returns it.
    * @param string $msg
    * @return string
    */
   protected function socket_send($msg)
   {
      // Send the message
      if (self::DEBUG) echo ">>>\n" . $this->hexdump($msg); // DEBUG
      if (strlen($msg)!=fwrite($this->socket, $msg)) {
         throw new SIMPLCommunicationError("error while sending data: ".bin2hex($msg)); 
      }

      // Read the first 4 bytes, they are supposed to have our token and the length
      $rx = fread($this->socket, 4);
      if (strlen($rx)!=4) {
         throw new SIMPLCommunicationError("data header read error, read: ".bin2hex($rx));
      }
      $header = unpack("vtoken/vlength",$rx);
      if ($header['token']>self::MAX_TOKEN || $header['token']<self::MIN_TOKEN) {
         throw new SIMPLCommunicationError("data header read error, unknown token {$header[token]} in: ".bin2hex($rx));
      }
      
      // Read the remainder
      $rx .= fread($this->socket, $header['length']);
      if (strlen($rx)!=$header['length']+4) {
         throw new SIMPLCommunicationError("data read error, incorrect length in: ".bin2hex($rx));
      }
      
      // Return the results
      if (self::DEBUG) echo "<<<\n" . $this->hexdump($rx); // DEBUG
      return $rx;
   }
      
   /**
    * Locates the name of the receiver, returns the receiver ID as an integer
    * @param string $receiver_name
    * @return int
    */
   protected function name_locate( $receiver_name ) {
      $rx = $this->socket_send(pack("vvVa20V", self::NAME_LOCATE, 28, -1, substr($receiver_name,0,20),-1));
      if (strlen($rx)!=32) throw new SIMPLCommunicationError("unexpected reply length: " . bin2hex($rx)); 
      $r = unpack('vtoken/vlength/Vfiller/a20name/Vrcvid',$rx);
      if ($r['token']!=self::REPLY_IT) throw new SIMPLCommunicationError("unexpected token {$r[token]} in reply to NAME_LOCATE");
      if ($r['rcvid']==0xFFFFFFFF || $r['rcvid']==-1) throw new SIMPLNameNotFound("Name '$receiver_name' not found.");
      return (int)$r['rcvid'];
   }
   
   /**
    * Attaches to the server
    * @param string $sender_name 
    * @return int
    */
   protected function name_attach( $sender_name ) {
      $r = $this->socket_send(pack("vvVa20VV", self::NAME_ATTACH, 32, 0, substr($sender_name,0,20),0,0));
      // Validate it
      if ( $r[0] != chr(self::REPLY_IT) ) {
         throw new SIMPLCommunicationError("Unexpected response to NAME_ATTACH: " . bin2hex($r));
      }
   }
   
   /**
    * Detaches from the receiver
    */
   protected function name_detach()
   {
      $this->socket_send(pack("vv", self::NAME_DETACH, 0));    
   }
   
   /**
    * Sends the message to the SIMPL receiver, returns the response as string. 
    * @param string $msg
    * @return string
    */
   public function Send ( $msg ) {
      $r = $this->socket_send(pack("vvV",self::SEND_IT,4+strlen($msg),$this->receiver_id).$msg);
      $data = substr($r,8);
      $rx = unpack("vtoken/vlength/Vfiller",$r);
      if ($rx['token']!=self::REPLY_IT) throw new SIMPLCommunicationError("unexpected token {$r[token]} in reply to SEND");
      if (($rx['length']-4) != strlen($data)) throw new SIMPLCommunicationError("received data length mismatch  in reply to SEND: " . bin2hex($msg));       
      return $data;
   }
   
   
};


?>
