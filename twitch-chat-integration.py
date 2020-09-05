# Following tutorial from Ryan Chesler titled "Twitch Pays Pokemon with Python 3.6 Tutorial"
# "pip install requests" may be necessary to run
# When modifying for your server change "PASS" "CHANNEL" and "OWNER"
import socket
import requests

# Defining the needed variables
SERVER = "irc.twitch.tv"
PORT = 6667
PASS = "oauth:s0z5ggucme1yhthadt9csk9gdc2f6q"
NICK = "Chat_Collection"
CHANNEL = "billchicken72"
OWNER = "billchicken72"

# Establishing the Connection
irc = socket.socket()
irc.connect((SERVER, PORT))
irc.send(("PASS " + PASS + "\n" + "NICK " + NICK + "\n" + "JOIN #" + CHANNEL + "\n").encode())

# Get through the initial connecting comments
def joinchat():
    while True:
        readbuffer_join = irc.recv(1024)
        readbuffer_join = readbuffer_join.decode()
        for line in readbuffer_join.split('\n'):
            print(line)
            if (loadingComplete(line)):
                return

# Determine if the final connecting comment has been reached
def loadingComplete(line):
    if ('End of /NAMES list' in line):
        return True
    else:
        return False

# Send a string in the Twitch chat
def sendMessage(message):
    message = "PRIVMSG #" + CHANNEL + " :" + message + "\n"
    irc.send(message.encode())
'''
def getData(line):
    print("Getting Data")
    splitUp = line.split(":")
    message = splitUp[2]

    user = splitUp[1].split("!")[0]
    return (user, message)
'''

# Send request to move the robot
request_URL = 'http://192.168.1.1'
def moveForward():
    print("Moving Forward")
    r = requests.get(request_URL + '/forward')

def moveBack():
    print("Moving Backwards")
    r = requests.get(request_URL + '/backward')

def turnRight():
    print("Turning to the right")
    r = requests.get(request_URL + '/right')

def turnLeft(): 
    print("Turning to the left")
    r = requests.get(request_URL + '/left')

# Connecting to the stream
joinchat()
sendMessage("Bot has joined the Channel!")

# Get the messages sent and see if they are a command
while True:
    readbuffer = irc.recv(1024).decode()
    for line in readbuffer.split("\n"):
        if (line == ""):
            continue
        message = line.split(":")[2]
        message = message.strip()
        if message == "forward":
            moveForward()
        elif message == "backward":
            moveBack()
        elif message == "left":
            turnLeft()
        elif message == "right":
            turnRight()
        else:
            sendMessage("Unknown Command")
