import os
import discord
import asyncio
import re

from dotenv import load_dotenv
from discord.ext import commands

intents = discord.Intents.default()
intents.members = True
intents.presences = True

load_dotenv()
TOKEN = os.getenv("DISCORD_TOKEN")

bot = commands.Bot(command_prefix = os.getenv("CMD_PHRASE"))

bot.load_extension(f'cogs.mainCmds')
bot.load_extension(f'cogs.xpOps')

bot.run(TOKEN)