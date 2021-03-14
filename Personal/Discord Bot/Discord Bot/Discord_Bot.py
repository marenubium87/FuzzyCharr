import os
import discord
import asyncio
import re

from dotenv import load_dotenv
from discord.ext import commands

intents = discord.Intents.default()
intents.members = True
intents.presences = True

msg_delay = 2

load_dotenv()
TOKEN = os.getenv("DISCORD_TOKEN")

#trusted users
trustedUsersList = ["Reynx", "Aerie", "Misa", "Ben"]

TRUSTED_USERS = {os.getenv(name.upper()): name for name in trustedUsersList}
client = discord.Client(intents = intents)

@client.event
async def on_ready():
    print("Logged in as " + client.user.name)
    print(client.user.id)
    print("Newton is online.", flush=True)

@client.event
async def on_message(message):
    if message.author == client.user:
        return
    elif str(message.author.id) not in TRUSTED_USERS:
        if "hi, newton" in message.content.lower():
            response = ("Hi, " + message.author.name + "\n"
                        "Your user ID is " + str(message.author.id))
        
    elif str(message.author.id) in TRUSTED_USERS:
        if "hi, newton" in message.content.lower():
            response = ("Hi, " + TRUSTED_USERS[str(message.author.id)] + "!")

        elif "bye, newton" in message.content.lower():
            response = ("Bye, " + TRUSTED_USERS[str(message.author.id)] + "!")
        elif re.search("am i \S+\?", message.content.lower()) is not None:
            wList = str(re.search("am i \S+\?", message.content.lower()).group(0)).split()
            word = wList[len(wList)-1]
            name = word[:-1]

            if name in (user.lower() for user in trustedUsersList):
                if TRUSTED_USERS[str(message.author.id)].lower() != name:
                    response = "No."
                else:
                    response = "Yes."
            else:
                response = "I do not know of this individual."
        else:
            response = ""
    
    await asyncio.sleep(msg_delay)
    if response != "":
        await message.channel.send(response)
    
client.run(TOKEN)