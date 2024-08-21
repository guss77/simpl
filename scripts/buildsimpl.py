import os, sys

# check for the fifo path environment variable
try:
	os.environ['FIFO_PATH']
except:
	print("The FIFO_PATH environment variable has not been set.")
	sys.exit()
	
# check for the fifo path directory
if not os.path.exists(os.environ['FIFO_PATH']):
	print("The FIFO_PATH directory does not exist.")
	sys.exit()
	
# check for the simpl home environment variable
try:
	os.environ['SIMPL_HOME']
except:
	print("The SIMPL_HOME environment variable has not been set.")
	sys.exit()

# check for the simpl home directory
if not os.path.exists(os.environ['SIMPL_HOME']):
	print("The SIMPL_HOME directory does not exist.")
	sys.exit()

# check for the simpl home directory
workPath = os.environ['SIMPL_HOME'] + "/python"
if not os.path.exists(workPath):
	print("The %s directory does not exist." %workPath)
	sys.exit()

# find whatever version of python will support the SIMPL extension library
vers = os.popen("ls -d1 /usr/include/python*").readlines()
numVers = len(vers)

if numVers == 0:
	print("Cannot find any C files in /usr/include to build the extended SIMPL \
library.")
	sys.exit()
else:
	print("The following python version(s) were found:\n")
	for i in range(numVers):
		print(vers[i][19:len(vers[i])-1])

while True:
	if sys.version > '3':
		ver = input("Choose a version for the SIMPL extended library> ")
	else:
		ver = raw_input("Choose a version for the SIMPL extended library> ")

	print("You have chosen python version %s" %ver)

	if sys.version > '3':
		decision = input("Is this correct (yes/no/quit)? y/n/q> ")
	else:
		decision = raw_input("Is this correct (yes/no/quit)? y/n/q> ")
		
	if decision == 'y':
		break
	elif decision == 'n':
		continue
	else:
		sys.exit()

# change working directory
os.chdir(workPath)

# make the extended simpl libraries/modules
print("\nCheck the %s/make.out file for a record of the make\n" %workPath)
str = "make" + " PYTHONVER=" + ver + " RELEASE=" + ver[0] + " | tee make.out"
os.system(str)


