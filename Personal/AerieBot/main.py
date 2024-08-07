import settings
import discord
from discord.ext import commands
from discord.ui import Button
from cogs.test import Greetings

logger = settings.logging.getLogger('bot')
    
class MyClass(commands.Converter):
    async def convert(self, ctx, argument):
        my_msg = ctx.message.content
        s = my_msg.find('say_hi')
        my_msg = my_msg[s + 7:]
        return f'{ctx.author} says {my_msg}'
    
class SimpleView(discord.ui.View):

    foo : bool = None

    async def disable_all_items(self):
        for item in self.children:
            item.disabled = True
        await self.message.edit(view=self)
        

    async def on_timeout(self) -> None:
        await self.message.channel.send('timed out')
        await self.disable_all_items()


    @discord.ui.button(label = 'my label here', style = discord.ButtonStyle.success)
    async def hello(self, interaction: discord.Interaction, button: discord.ui.Button):
        await interaction.response.send_modal(FeedbackModal())
        #self.stop()

    @discord.ui.button(label = 'my label here', style = discord.ButtonStyle.red)
    async def cancel(self, interaction: discord.Interaction, button: discord.ui.Button):
        await interaction.response.send_message('foo now false')
        self.foo = False
        #self.stop()

class FeedbackModal(discord.ui.Modal, title='Send Feedback'):
    feedback_title = discord.ui.TextInput(
        style=discord.TextStyle.short,
        label = 'Title',
        required=True,
        placeholder='Give a title here'
    )

    message = discord.ui.TextInput(
        style=discord.TextStyle.long,
        label='Title',
        required=True,
        max_length=500,
        placeholder='Blah blah'
    )

    async def on_submit(self, interaction: discord.Interaction):
        pass

    async def on_error(self, interaction: discord.Interaction, error):
        pass



def run():
    intents = discord.Intents.default()
    intents.message_content = True

    bot = commands.Bot(command_prefix='Hey, AerieBot: ', intents=intents)

    @bot.event
    async def on_ready():

        logger.info(f'user: {bot.user} ID: {bot.user.id}')
        await bot.load_extension('cogs.test')
        #await bot.tree.copy_global_to(guild=settings.GUILD_ID)
        #await bot.tree.sync(guild=settings.GUILD_ID)
    
    '''
    @bot.command()
    async def feedback(interaction: discord.Interaction):
        feedback_modal = FeedbackModal()
        await interaction.response.send_modal(feedback_modal)
    '''



    @bot.command()
    async def ping(ctx):
        await ctx.send('pong')

    @bot.command()
    # * allows acceptance of multiple args (in this case, multiple words)
    async def say(ctx, *what):
        await ctx.send(' '.join(what))

    @bot.command()
    async def joined(ctx, who : discord.Member):
        await ctx.send(who.display_name + ' ' + str(who.id))

    @bot.command()
    async def say_hi(ctx, msg: MyClass):
        await ctx.send(msg) 


    @bot.command()
    async def raid_call(ctx):
        embed = discord.Embed(
            color=discord.Color.dark_blue(),
            description = 'description here',
            title = 'title here'
        
        )
        embed.set_footer(text='footer here')
        embed.set_author(name='author')

        embed.add_field(name='Field here', value = 'Text inside field')
        embed.add_field(name = 'Second Field', value = 'Text for second field here')

        await ctx.send(embed=embed)


    @bot.command()
    async def button(ctx):
        view = SimpleView(timeout = 3)

        
        message = await ctx.send(view = view)
        view.message = message

        await view.wait()
        #await view.disable_all_items()
        if view.foo == None:
            await ctx.send('foo is None')
        elif view.foo == True:
            await ctx.send('foo is True')
        else:
            await ctx.send('foo is False')
            

    bot.run(settings.DISCORD_API_KEY, root_logger=True)

if __name__ == '__main__':
    run()