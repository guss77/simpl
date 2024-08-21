<?php

/*

   SIMPL tclSurrogate Protocol Demo - Online Sudoku Solver

   Copyright (c)2011 Dimitri Tarassenko 

   This software is in the public domain.
   Permission to use, copy, modify, and distribute this software and its
   documentation for any purpose and without fee is hereby granted,
   without any conditions or restrictions.
   This software is provided "as is" without express or implied warranty.
   
   If you discover a bug or add an enhancement contact us on the
   SIMPL project mailing list.

*/

require_once "SIMPL.php";

/**
 * A class representing a 4x4, 9x9 or 16x16 sudoku puzzle.
 * @author dt
 *
 */
class Sudoku {

   // Puzzle dimensions
   public $size = 0;
   
   // 2D array of cells
   public $cell;  

   /**
    * Constructs a blank puzzle of given size (9,16,etc.)
    * @param $size
    */
   public function __construct($size)
   {
      $this->size = $size;
      $this->cell = array_fill(0,$size,array_fill(0,$size,0));
   }
   
   /**
    * Builds an instance of Sudoku based on the puzzle cells in string $s. $s can
    * be either 16, 81, 256 characters long. 
    * @param $s
    */
   public static function getInstanceFromString($s)
   {
      $size = sqrt(strlen($s)); 
      //if (!is_int($size)) return null;
      $puzzle = new self($size);
      for ($r=0;$r<$size;$r++) {
         for ($c=0;$c<$size;$c++) {
            $puzzle->cell[$r][$c] = hexdec($s[$r*$size+$c]);
         }
      }
      return $puzzle;
   }
   
   /**
    * Returns a test puzzle number $n
    * @param $n
    */
   public static function getTestInstance($n)
   {
      switch ($n) {
         // from http://icanprogram.ca/sudoku
         case 2: return self::getInstanceFromString("000002700040000035017306000005700014980000076170004300000607820320000090008200000"); 
         // from somewhere else:
         case 1: return self::getInstanceFromString("080000005205706340906835000001000070020408090030000100000541706074203509600000030");
         // from: http://icanprogram.ca/sudokutcl/
         default: return self::getInstanceFromString("000700100081400006000010340109000050000607000060000403034020000900006820002005000");
      }
   }

   /**
    * Returns a string representation of the puzzle for debugging/printing purposes
    * @return string
    */
   public function __toString()
   {
      $s = "";
      //$cell_group_size = sqrt($this->size);
      for ($r=0;$r<$this->size;$r++) {
         //if ($r && ($r)%$cell_group_size==0) $s.="\n";
         for ($c=0;$c<$this->size;$c++) {
            //if ($c && ($c)%$cell_group_size==0) $s.=" ";
            $s .= $this->cell[$r][$c] ? $this->cell[$r][$c] : ".";
         }
         $s .= "\n";
      }
      return $s;
   }
}

/**
 * A class that solves Sudoku puzzles using the SIMPL server.
 * @author dt
 *
 */
class SIMPLSudokuSolver extends SIMPLSender
{
   // Sudoku Engine tokens
   const etDO_9                 = 0;
   const etDO_16                = 1;
   const etPUZZLE_FAILURE       = 2;
   const etERROR                = 3;
   const etBAD_TOKEN            = 4;
   const etMAX_ENGINE_TOKENS    = 5;

   
   // Last error description
   public $error = "";
   
   /**
    * Ctor
    */
   public function __construct()
   {
      // We know where we are going to connect. Let's fo it.
      parent::__construct("tcp://icanprogram.ca:8000", "ENGINE", "PHPSUDOKUSOLVER");
   }   
   
   /**
    * Solves the Sudoku puzzle in $puzzle. Returns either a solved puzzle, or FALSE if an
    * error occured. In this case $this->error will be set. 
    *  
    * @param Sudoku $puzzle
    * @return Sudoku
    */
   public function solve( Sudoku $puzzle )
   {
      try {      
         // Send the message to the engine
         $rx = $this->Send($this->puzzleToMessage($puzzle));
         // See what we get in the response
         switch ($rx[0]) {
            case chr(self::etERROR) :
               $this->error = "Engine error";
               return false;
            case chr(self::etPUZZLE_FAILURE) :
               $this->error = "Puzzle failure";
               return false;
            case chr(self::etDO_9) : // success!
            case chr(self::etDO_16) :
               $this->error = null;
               return $this->messageToPuzzle($rx);   
            default:
               $this->error = "Unexpected token ".ord($rx[0])." in response from the engine";
               return false;
         }
      }
      catch (SIMPLException $e) { // Something went wrong on the tclSurrogate protocol level
         $this->error = "SIMPL Transport Error: ".$e->getMessage();
         return false;
      }
   }
   
   /**
    * Converts a puzzle to a binary message suitable for the SIMPL Sudoku Engine
    * @param Sudoku $puzzle
    * @return string
    */
   private function puzzleToMessage( Sudoku $puzzle )
   {
      // Our message is:
      // typedef struct {
      //    int token; // DO_9 or DO_16
      //    char elements[256]; // maximum possible size
      // } SUDOKU_MSG;
      $msg = pack("V", $puzzle->size == 9 ? self::etDO_9 : self::etDO_16 );
      for ($r=0;$r<$puzzle->size;$r++) {
         for ($c=0;$c<$puzzle->size;$c++) {
            $msg .= $puzzle->cell[$r][$c] ? dechex($puzzle->cell[$r][$c]) : " ";
         }
      }
      return $msg;
   }
   
   /**
    * Converts a message received from the SIMPL Sudoku Engine into a puzzle.
    * @param string $msg
    * @return Sudoku
    */
   private function messageToPuzzle( $msg ) 
   {
      // We pretty much have characters already there in the packet it it's a response from the engine.
      return Sudoku::getInstanceFromString(substr($msg,4));
   } 
   
}

/**
 * A Sudoku puzzle class that can be instantited based on the data we get from
 * the POST request
 * @author dt
 */
class SudokuWebPuzzle extends Sudoku
{
   public function __construct() {
      parent::__construct(9);
      for ($i=0;$i<$this->size;$i++) {
         for ($j=0;$j<$this->size;$j++) {
            $this->cell[$i][$j] = (int)$_POST["i-$j-$i"];            
         }
      }
   }   
}

/**
 * Sudoku Web UI
 */
class SudokuWebUI {

   public function run() {
      
      // Figure out what board to print
      $message = '';
      switch ($_POST['action']) {
         case 'solve':
            $puzzle = new SudokuWebPuzzle();
            $solver = new SIMPLSudokuSolver();
            $solution = $solver->solve($puzzle);
            if ($solution!==false) {
               $puzzle = $solution; // need to print the solution now!
               $message = "<span style=\"color:green;\">Solved OK</span>";
            } else {
               $message = "<span style=\"color:red;\">".$solver->error."</span>";
            }
            break;
         case 'sample1': 
            $puzzle = Sudoku::getTestInstance(0);
            $message = "Sample 1 Loaded."; 
            break; 
         case 'sample2': 
            $puzzle = Sudoku::getTestInstance(1);
            $message = "Sample 2 Loaded."; 
            break; 
         case 'sample3': 
            $puzzle = Sudoku::getTestInstance(2);
            $message = "Sample 3 Loaded."; 
            break; 
         case 'clear':
         default:  
            $puzzle = new Sudoku(9);
      }
      $this->printBoard($puzzle,$message);
   }
   
   private function printBoard(Sudoku $puzzle, $message) {
      $s = "<table id=\"sudoku{$puzzle->size}\">";
      for ($i=0;$i<$puzzle->size;$i++) {
         $s .= '<tr id="r'.$i.'">';
         for ($j=0;$j<$puzzle->size;$j++) {
            $s = $s . '<td class="c'.$j.'">' .
               "<input name=\"i-$j-$i\" id=\"i-$j-$i\" ".
                  "onfocus=\"onInputFocus(this);\" ".
                  "onblur=\"onInputBlur(this);\" ".
                  "onkeydown=\"onInputKeyDown(event, this);\" ".
                  "value=\"".($puzzle->cell[$i][$j] ? $puzzle->cell[$i][$j] : "")."\" size=\"1\" maxlength=\"1\" ".
                  "class=\"suinput\" />";
         }
         $s .= "</tr>";
      }
      $s .= "</table>";
      echo $s;
      echo "<div id=\"message\">$message&nbsp;</div>";
   }
   
}



?>
<html>
<head>
<title></title>
<style type="text/css">
   h1,body,div {
      font-family: Verdana, Tahoma;
   }

   #sudoku9 {
      border-collapse: collapse;
   }
   #sudoku9 td {
      width: 50px;
      height: 50px;
      border: 1px solid #aaa;
      background: #f0f0f0;
      padding: 0px;
   }
   #sudoku9 #r3 td, #sudoku9 #r6 td {
      border-top: 2px solid #666;
   }
   #sudoku9 td.c3, #sudoku9 td.c6 {
      border-left: 2px solid #666;
   }
   #sudoku9 div.solved, #sudoku9 div.initial, #sudoku9 div.error, #sudoku9 input.suinput {
      background: #cfc;
      text-align: center;
      font: bold 18pt Verdana;
      line-height: 48px;
      height:48px;
   }
   #sudoku9 div.solved {
      background: #8f8;
   }
   #sudoku9 div.error {
      background: red;
   }
   #sudoku9 table.options {
      border: none !important;
      padding: 0px;
      margin-left: 9px;
   }
   #sudoku9 table.options td {
      border: none !important;
      padding: 0px;
      margin: 0px;
      color: #aaa;
      width: 11px;
      height: 12px;
      vertical-align: middle;
      text-align: center;
      font: normal 7pt/7pt Verdana;
   }
   #sudoku9 table.justchanged td, #sudoku9 div.justchanged {
      background: #ff6;
      color: black;
   }
    
   #sudoku9 input.suinput {
      border: none;
      height: 40px;
      line-height: 30px;
      background: none;
      margin: 0px;
      width: 40px;
      margin-left: 5px;
      
      /* IE */
      voice-family: "\"}\""; 
      voice-family: inherit;
      padding-top: 5px;
      
   }
   #sudoku9 input.suinput-active {
      background: #fff;
   }
   #sudoku9 input.suinput-filled {
      background: #cfc;
   }
   #tracer, #console {
      font: normal 7pt Verdana;
   }
   #buttons {
      padding-top: 10px;
   }
   #message {
      padding: 10px 0px;
      font-size: 12px;
      font-weight: bold;
   }
</style>
<script type="text/javascript">

function onInputFocus(elem) {
   elem.className = 'suinput suinput-active';
}

function onInputBlur(elem) {
   if ( isNaN(elem.value) || elem.value=='0' ) elem.value='';
   elem.className = 'suinput';
   /*
   if (elem.value == '') elem.className = 'suinput';
   else elem.className = 'suinput suinput-filled';
   */
}

function inputName(x,y) { // provides an element ID for an input at cell x,y
   return "i-"+x+"-"+y; 
}


function onInputKeyDown(event, element) {
   //alert(event.keyCode)
   var code = event.keyCode
   var c,i,j;
   switch (code)  {
   case 37: //left
      c = parseInt(element.name.charAt(2))-1;
      if (c<0) c = this.sizeX-1;
      document.getElementById(inputName(c,parseInt(element.name.charAt(4)))).focus();
      break;
   case 38:
      c = parseInt(element.name.charAt(4))-1;
      if (c<0) c = this.sizeY-1;
      document.getElementById(inputName(parseInt(element.name.charAt(2)),c)).focus();
      break;
   case 39:
      c = parseInt(element.name.charAt(2))+1;
      if (c==this.sizeX) c = 0;
      document.getElementById(inputName(c,parseInt(element.name.charAt(4)))).focus();
      break;
   case 40:
      c = parseInt(element.name.charAt(4))+1;
      if (c==this.sizeY) c = 0;
      document.getElementById(inputName(parseInt(element.name.charAt(2)),c)).focus();
      break;
   case 8: // del
      break;
   case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57: case 58: case 59: // numbers
      element.value = '';
      break;
   default:
      //alert(code)
   }
}

</script>
</head>
<body onload="document.getElementById('i-0-0').focus();">
<h1>SIMPL PHP Sudoku Client</h1>

<form method="post">
<div id="board"><?php 
   $ui = new SudokuWebUI();   
   $ui->run();
?></div>

<div id="buttons">
<input type="submit" name="action" value="clear" />&nbsp;&nbsp;&nbsp;&nbsp;
<input type="submit" name="action" value="sample1" />
<input type="submit" name="action" value="sample2" />
<input type="submit" name="action" value="sample3" />&nbsp;&nbsp;&nbsp;&nbsp;
<input type="submit" name="action" value="solve" />
</div>
</form>

</body>
</html>
