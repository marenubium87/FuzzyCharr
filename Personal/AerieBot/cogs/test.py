import discord
from discord.ext import commands

class Greetings(commands.Cog):
    def __init__(self, bot):
        self.bot = bot
    
    '''
    #this is how to add a behavior to be done on a triggered event
    @commands.Cog.listener()
    async def on_message(self, message: discord.Message):
        await message.add_reaction('👒')
    '''
    

    @commands.command()
    async def hello(self, ctx, *, member: discord.Member):
        await ctx.send("Hello {member.name}")



async def setup(bot):
    await bot.add_cog(Greetings(bot))
        