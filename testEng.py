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
command = ['bin/studio', 'ExampleInput.txt']
configFilePath = 'ExampleInput.txt'


usage = "-"*20 + "\n\033[1;32mUsage:\n\n[*]\033[0m Place the script in the project's dir. Make sure there exists a config file '" + configFilePath + "'. Make sure there is a '" + scenariosPath + "' directory. Each scenario should be a text file of commands, and expected output; scenario files should have the extension '"\
+ sceneFileExtension +\
"'. Last command in each scenario should be 'closeall'.\n"\
"\n\n\033[1;32m[*]\033[0m The script is going to mention which scenarios failed. For the failed scenarios, the differences between the expected output and the actual one will be dumped as .html files in the '" + outputsPath + "' dir (for convenience of viewing in-browser).\n"\
"\n\n\033[1;32m[*]\033[0m Format of a .scene file:\n"\
"\t<series of commands, ending with 'closeall'>\n"\
"\t<blank line>\n"\
"\t"+sceneSeparator+\
"\t<blank line>\n"\
"\t<expected output>\n"\
"\n\n\033[1;32m[*]\033[0m This script was written to run in a linux terminal (may or may not run on windows). To run the script you need python (can be installed by running 'sudo apt install python3 -y' on ubuntu-based/debian-based systems.)\n\n"+"-"*20


if "-u" in sys.argv or "--usage" in sys.argv or not os.path.isdir(scenariosPath):
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
			
			with subprocess.Popen(command,stdout=subprocess.PIPE,stderr=subprocess.STDOUT,stdin=subprocess.PIPE,bufsize=1, universal_newlines=True) as p:
				stdout,stderr = p.communicate(inputs)
			
			if stdout != outputs:
				print("\033[1;31m[!]\033[0m", file, "\033[1;31mFAILED\033[0m")
				
				with open(outputsPath+"/" + file.replace(sceneFileExtension, failedOutputExtension), "w") as f:
					f.write(difflib.HtmlDiff().make_file(outputs.split("\n"), stdout.split("\n"), 'EXPECTED', 'OCCURED'))
			else:
				print("[+]", file, "passed")

print()

