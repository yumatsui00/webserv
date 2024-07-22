#include "Command.hpp"

int	Command::mode( Server &server ) {
	if (!(2 <= _divCmd.size() && _divCmd.size() <= 4))
		return (461);
	Channel *channel = server.findChannel(_divCmd[1]);
	if (channel == NULL)
		return (403);
	if (!channel->isExist(_user))
		return (442);
	if (_divCmd.size() == 2)
		return (displayCurrentMode(channel));
	if (!channel->isOperator(_user))
		return (482);
	return (modeChanger( server, channel, _divCmd.size() ));
}

int	Command::displayCurrentMode( Channel *channel ) {
	std::string msg;

	msg = ":ft_irc 324" + _user->getNickName() + _divCmd[1] + " +";
	if ((channel->getMode(MODE_K)))
		msg += "k";
	if ((channel->getMode(MODE_L)))
		msg += "l";
	if ((channel->getMode(MODE_I)))
		msg += "i";
	if ((channel->getMode(MODE_T)))
		msg += "t";
	if ((channel->getMode(MODE_O)))
		msg += "o";
	if ((channel->getMode(MODE_K)))
		msg += " " + channel->getPass();
	if ((channel->getMode(MODE_L))) {
		size_t	tmp = channel->getMaxusers();
		std::ostringstream oss;
		oss << tmp;
		msg += " " + oss.str();
	}
	msg += "\n";
	//!ft_semd(fd, msg) fd = だれ
	return (0);
}

int		Command::modeChanger( Server &server, Channel *channel, size_t size ) {
	bool		msg_permission = true;
	std::string mod = _divCmd[1], arg1 = _divCmd[2], arg2;
	std::string msg = ":" + _user->getPrefix() + " MODE" + mod + " " + arg1;

	if (size == 3)
		msg += "\n";
	else if (size == 4) {
		arg2 = _divCmd[3];
		msg += " " + arg2 + "\n";
	}

	if (mod == "+i" && size == 3)
		channel->setMode(MODE_I, true);
	else if (mod == "-i" && size == 3)
		channel->setMode(MODE_I, false);
	else if (mod == "+t" && size == 3)
		channel->setMode(MODE_T, true);
	else if (mod == "-t" && size == 3)
		channel->setMode(MODE_T, false);
	else if (mod == "+k" && size == 4) {
		channel->setMode(MODE_K, true);
		channel->changePass(arg2);
	}
	else if (mod == "-k" && size == 4)
		channel->setMode(MODE_K, false);
	else if (mod == "+l" && size == 4) {
		int limit = checkNum(arg2);
		if (limit < 1)
			return (401); //!err banngou  check
		channel->setMode(MODE_L, true);
		channel->changeLimit(size_t(limit));
	}
	else if (mod == "-l" && size == 3)
		channel->setMode(MODE_L, false);
	else if ((mod == "+o" || mod == "-o") && size == 4) {
		User* target = channel->nick2User(arg2);
		if (target == NULL)
			return (441);
		if (mod == "+o")
			channel->becomeOperator(target);
		else
			channel->ceaseOperator(target);
	}
	else
		msg_permission = false;
	if (msg_permission == true)
		//ft_send(fd, aef); fd = すべてのひと

	(void)server;//!for compile
	return (0);
}

int		Command::checkNum( std::string num ) {
	int		number;

	std::istringstream iss(num);
	iss >> number;
	if (iss.eof() && !iss.fail())
		return (-1);
	return number;
}