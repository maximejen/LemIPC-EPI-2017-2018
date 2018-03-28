#!/usr/bin/env python3
from subprocess import run, check_output
from getopt import getopt
from random import seed, randrange
from time import sleep
import sys, re, os

seed(os.getpid())

global path
path = "./lemipc " + check_output("pwd", shell = True).decode("utf8").strip() + " "

def help():
	progname = re.findall("([^/.]+)$", sys.argv[0])[0]
	print("USAGE:")
	print("	" + progname, end = "")
	print(""" [options]
DESCRIPTION:
	default		asks for default mode (3 teams and 10 members for each)

OPTIONS:
	-h, --help			Displays help.
	-g, --graphical			Use graphical interface.
	-u, --unique-team={x,id}	Creates a team with "id" for its id and "x" members.
	-l, --time-limit={time}		Set a time limit that kills the prgrams after "time" seconds.
	-t, --teams={nbr}		Asks for "nbr" teams with default size (or the -m size).
	-m, --members={size}		Asks for "size" members in each team, by default there are 3 teams.
""")
	sys.exit(1)
def check_args(args):
	ret = {
		"teams": 3,
		"members": 10,
		"time": "",
		"unique": [],
		"ids": [ "0" ],
		"started": False
	}
	optlist, args = getopt(args[1:], 'u:t:l:m:hg', [
		'unique-team=', 'teams=', 'time-limit=', 'members=', 'help', 'graphical'])
	for opt in optlist:
		if opt[1] == "":
			if opt[0] in ("-h", "--help"):
				help()
			elif opt[0] in ("-g", "--graphical"):
				global path
				path += " -g "
		else:
			if opt[0] in ("-m", "--members"):
				if not opt[1].isdigit():
					help()
				ret["members"] = int(opt[1])
			elif opt[0] in ("-l", "--time-limit"):
				if not opt[1].isdigit():
					help()
				ret["time"] = "timeout " + opt[1] + " "
			elif opt[0] in ("-t", "--teams"):
				if not opt[1].isdigit():
					help()
				ret["teams"] = int(opt[1])
			elif opt[0] in ("-u", "--unique-team"):
				if not re.match("^\d+,\d+$", opt[1]):
					help()
				args = re.findall("^(\d+),(\d+)$", opt[1])
				ret["unique"].append({ "id": args[0][1], "members": args[0][0]})
	return ret
def make_file():
	run("make", shell = True)
	if not os.access("lemipc", os.X_OK):
		print("No lemipc executable found.")
		sys.exit(84)
def clean():
	run("make fclean", shell = True)
	run("rm .nocarelemipc", shell = True)
def create_unique(dict):
	for team in dict["unique"]:
		if not int(team["id"]) in dict["ids"]:
			# print("Creating team of " + team["members"] + " members with id : " + team["id"] + ".")
			for i in range(0, int(team["members"])):
				run(dict["time"] + path + team["id"] + " &", shell = True)
				if not dict["started"]:
					dict["started"] = True
					global path
					path = "> .nocarelemipc " + path
			dict["ids"].append(int(team["id"]))
def create_teams(dict):
	for i in range(0, dict["teams"]):
		id = "0"
		while id in dict["ids"]:
			id = str(randrange(1, 100000))
		# print("Creating team of " + str(dict["members"]) + " members with id : " + str(id) + ".")
		create_members(id, dict["members"])
def create_members(id, numbers):
	for i in range(0, numbers):
		# print(dict["time"] + path + id)
		run(dict["time"] + path + id + " &", shell = True)
		if not dict["started"]:
			dict["started"] = True
			global path
			path = "> .nocarelemipc " + path

# Main -------------------------------------------------------------------------
dict = check_args(sys.argv)
make_file()
run("ipcrm --all", shell = True)
create_unique(dict)
create_teams(dict)
clean()