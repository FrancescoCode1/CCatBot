#include <dpp/dpp.h>


const std::string    BOT_TOKEN    = "TOKEN_HERE";
const dpp::snowflake MY_GUILD_ID  =  /*guild here*/;

int main()
{
    /* Create bot cluster */
    dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);

    /* Output simple log messages to stdout */
    bot.on_log(dpp::utility::cout_logger());

    /* Handle slash command */
    bot.on_interaction_create([&bot](const dpp::interaction_create_t& event) {
         if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
         }
         if (event.command.get_command_name() == "menu") {
             

            event.reply(dpp::ir_channel_message_with_source, dpp::message(event.command.channel_id, "Choose your Weapon!")
                .add_component(
                    dpp::component().add_component(
                        dpp::component().set_type(dpp::cot_selectmenu).
                        set_placeholder("Pick something").
                        add_select_option(dpp::select_option("label1", "value1", "description1").set_emoji(u8"😄")).
                        add_select_option(dpp::select_option("label2", "value2", "description2").set_emoji(u8"🙂")).
                        set_id("myselid")
                )
            )
          );
              
         }
    });

    /* Register slash command here in on_ready */
    bot.on_ready([&bot](const dpp::ready_t& event) {
        /* Wrap command registration in run_once to make sure it doesnt run on every full reconnection */
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.guild_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id), MY_GUILD_ID);
            bot.guild_command_create(dpp::slashcommand("menu", "Check Version of bot", bot.me.id), MY_GUILD_ID);
        }
    });

    /* Start the bot */
    bot.start(false);

    return 0;
}
