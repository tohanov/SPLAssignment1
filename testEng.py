#!/usr/bin/python3
import subprocess
import os
import sys
import difflib
import shutil

scenariosPath = 'tests/scenarios'
outputsPath = 'tests/outputs'
sceneFileExtension = '.scene'
sceneSeparatorPrefix = '\n'
sceneSeparator = '*'*5+'\n'
sceneSeparatorSuffix = '\n'
# passedOutputExtension = ".pass"
failedOutputExtension = ".FAIL.html"
configFilePath = 'ExampleInput.txt'
studioCommand = ['bin/studio', configFilePath]
valgrindCommand = ['valgrind', '-v', '--leak-check=full', '--show-reachable=yes'] + studioCommand
scriptName = os.path.basename(__file__)

usageSeparator = "-"*20
usage = usageSeparator + "\n\033[1;32mUsage: './" + scriptName + "'\n\n[*]\033[0m\tPlace the script in the project's dir.\n"\
"\tMake sure the config file '" + configFilePath + "' exists.\n"\
"\tMake sure the directory '" + scenariosPath + "' exists.\n"\
"\tEach scenario should be a text file of commands, and expected output; scenario files should have the extension '"\
+ sceneFileExtension +\
"'.\n"\
"\tLast command in each scenario should be 'closeall'.\n"\
"\n\n"\
"\033[1;32m[*]\033[0m\tThe script is going to mention which scenarios failed.\n"\
"\tFor the failed scenarios, the differences between the expected output and the actual one will be dumped as *.html files in the '" + outputsPath + "' dir (to be viewed in-browser.)n"\
"\n\n"\
"\033[1;32m[*]\033[0m\tFormat of a *" + sceneFileExtension + " file:\n"\
"\n"\
"\t\t<series of commands, ending with 'closeall'>\n"\
"\t\t<blank line>\n"\
"\t\t"+sceneSeparator+\
"\t\t<blank line>\n"\
"\t\t<expected output>\n"\
"\n\n\033[1;32m[*]\033[0m \tThis script was written to run in a linux terminal (may or may not run on windows).\n"\
"\tTo run the script you need python (can be installed by running 'sudo apt install python3 -y' on ubuntu-based/debian-based systems.)\n\n"\
"You can view this usage information later by running './" + scriptName + " -u' or './" + scriptName + " --usage'.\n"+usageSeparator


if "-u" in sys.argv or "--usage" in sys.argv:
	print(usage)
	exit()
	
if not os.path.isdir(scenariosPath):
	print("\033[1;31m[!]", scenariosPath, "dir wasn't found.\033[0m")

	print(usage)
	exit()


if os.path.isdir(outputsPath):
	shutil.rmtree(outputsPath)
os.mkdir(outputsPath)


for file in os.listdir(scenariosPath):
		if file.endswith(sceneFileExtension):
			print("\n[*] running", file)
			
			with open(scenariosPath+"/" + file) as f:
				testText = f.read()
			
			inputs,outputs = testText.split(sceneSeparatorPrefix + sceneSeparator + sceneSeparatorSuffix, 1)
			
			with subprocess.Popen(valgrindCommand, stdout=subprocess.PIPE,stderr=subprocess.STDOUT,stdin=subprocess.PIPE,bufsize=1, universal_newlines=True) as p:
				stdout,stderr = p.communicate(inputs)
				p.wait()

				if p.returncode != 0 or\
					not "definitely lost: 0" in stdout or\
					not "indirectly lost: 0" in stdout or\
					not "possibly lost: 0" in stdout or\
					not "suppressed: 0" in stdout:
					print("\033[1;31m[!]\033[0m valgrind check for ", file, "\033[1;31mFAILED\033[0m")
				else:
					print("[+] valgrind check for ", file, "passed")


			with subprocess.Popen(studioCommand, stdout=subprocess.PIPE,stderr=subprocess.STDOUT,stdin=subprocess.PIPE,bufsize=1, universal_newlines=True) as p:
				stdout,stderr = p.communicate(inputs)
			
			if stdout != outputs:
				print("\033[1;31m[!]\033[0m output check for ", file, "\033[1;31mFAILED\033[0m")
				
				with open(outputsPath+"/" + file.replace(sceneFileExtension, failedOutputExtension), "w") as f:
					f.write(difflib.HtmlDiff().make_file(outputs.split("\n"), stdout.split("\n"), 'EXPECTED', 'OCCURED'))
			else:
				print("[+] output check for ", file, "passed")

print()

