#ifndef SERVER_HPP
# define SERVER_HPP

#include "all.hpp"

class Server {
private:
	std::vector<User*>		_Users;
	std::vector<Channel*>	_Channels;
	std::string				_password;
public:
	Server();
	~Server();

	Channel*	findChannel( std::string ch_name );
	std::string	getPassword( void );
	std::vector<Channel*>	getChannels( void );
	User*		nick2User(std::string nick);
	User*		fd2User(int fd);

	void		addChannel( Channel *new_Ch );
	void		delChannel( Channel *ch );

	void		addUser(int fd);//kaz
	void		delUser(int fd);//kaz

};

#endif