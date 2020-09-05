# Following tutorial from Ryan Chesler titled "Twitch Pays Pokemon with Python 3.6 Tutorial"
import socket

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

def joinchat():
    while True:
        readbuffer_join = irc.recv(1024)
        readbuffer_join = readbuffer_join.decode()
        for line in readbuffer_join.split('\n'):
            print(line)
            if (loadingComplete(line)):
                return

def loadingComplete(line):
    if ('End of /NAMES list' in line):
        return True
    else:
        return False

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

def moveForward():
    print("Moving Forward")

def moveBack():
    print("Moving Backwards")

def turnRight():
    print("Turning to the right")

def turnLeft(): 
    print("Turning to the left")

joinchat()
sendMessage("Bot has joined the Channel!")

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
