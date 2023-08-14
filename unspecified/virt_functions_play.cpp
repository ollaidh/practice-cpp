#include <gtest/gtest.h>
#include <string>


class Command {
public:
    Command() = default;
    virtual ~Command() = default;
    virtual std::string execute() = 0;
};

class CommandHelp : public Command {
    std::string execute() override {
        return "HELP";
    }
};

class CommandBuy : public Command {
    std::string execute() override {
        return "BUY";
    }
};

class CommandSpent : public Command {
    std::string execute() override {
        return "SPENT";
    }
};

class CommandDel : public Command {
    std::string execute() override {
        return "DEL";
    }
};


class CommandHandler {
private:
    std::map<std::string, std::shared_ptr<Command>> commands = {
            {"help", std::make_shared<CommandHelp>()},
            {"buy", std::make_shared<CommandBuy>()},
            {"delete", std::make_shared<CommandDel>()},
            {"spent", std::make_shared<CommandSpent>()}
    };
public:
    std::string HandleCommand(std::string const &command) {
        return commands[command]->execute();
    };
};



TEST(commands, cmd) {
    CommandHandler cm;
    ASSERT_EQ("HELP", cm.HandleCommand("help"));
    ASSERT_EQ("BUY", cm.HandleCommand("buy"));
    ASSERT_EQ("DEL", cm.HandleCommand("delete"));
    ASSERT_EQ("SPENT", cm.HandleCommand("spent"));
}
