#ifndef __PUBLISHER_H_
#define __PUBLISHER_H_

#include "transport_udp.h"
#include <string>
#include <map>

namespace pcs{

template<typename T>
class Publisher{
public:
	Publisher();
	~Publisher()
	{
		delete[] sendBuff;
	}
	
	Publisher( const Publisher &obj ): addr_( obj.addr_ ),
					port_( obj.port_ ),
					transport( obj.transport )
	{
		memcpy( recvBuff, obj.recvBuff, 8 );
		memcpy( sendBuff, obj.sendBuff, sizeof( T ) + 1 );
	}

	Publisher& operator=( const Publisher &other )
	{
		if( this == &other )	return *this;
		
		addr_ = other.addr_;
		port_ = other.port_;
		transport = other.transport;
		memcpy( recvBuff, other.recvBuff, 8 );
                memcpy( sendBuff, other.sendBuff, sizeof( T ) + 1 );
	}

	void setSocketInfo( std::string addr, int port );
	
	void createAPublisher(  );

	void addSubscribersInfo();

	void publish( T &data );

	int getPublisherFd() const
	{
		return transport->getServerFd();
	}	

private:
	Transport *transport;	

	std::string addr_;
	int port_;
	
	//T data;
	
	unsigned char recvBuff[8];
	unsigned char *sendBuff;

	int subscribersCount;
	int size;

protected:
//	static std::map<int, std::string> destInfoMap;
};

static std::map<int, std::string> destInfoMap;

template<typename T>
Publisher<T>::Publisher(): subscribersCount( 0 ), size( 0 )
{
	transport = new TransportUDP;
	size  = sizeof( T ) + 1;
	sendBuff = new unsigned char[ size ];
	memset( sendBuff, 0, size );
}

template<typename T>
void Publisher<T>::setSocketInfo( std::string addr, int port )
{
        addr_ = addr;
        port_ = port;
}

template<typename T>
void Publisher<T>::createAPublisher(  )
{
	
	if( !transport->initSocketServer( port_ ) ){
		exit(-1);
	}
	std::cout<<"------------------- Init A Publsher ---------------------"<<std::endl;

	while( 1 ){
		addSubscribersInfo();
	}
}

template<typename T>
void Publisher<T>::publish( T &data )
{
	memset( sendBuff, 0, size );
	memcpy( sendBuff, &data, sizeof( data ) ) ;
	for( auto it = destInfoMap.begin(); it != destInfoMap.end(); it ++ ){
		struct sockaddr_in destAddr;
		destAddr.sin_family = AF_INET;
		destAddr.sin_addr.s_addr = inet_addr( it->second.c_str() );
		destAddr.sin_port = htons( it->first );
	
		int ret = transport->write( transport->getServerFd(), sendBuff, sizeof( data ), destAddr );
		if( ret < 0 ){
			std::cerr<<"publish failed ..."<<ret<<std::endl;
		}
		else std::cerr<<"published: "<<ret<<std::endl;
	}
}

template<typename T>
void Publisher<T>::addSubscribersInfo()
{
	std::cout<<" fd =  "<<transport->getServerFd()<<std::endl;
	int fd = transport->getServerFd();
	
	struct sockaddr_in addr;
        socklen_t addr_len;
        int ret = recvfrom( fd, recvBuff, sizeof(recvBuff), 0, ( struct sockaddr* )&addr, &addr_len );
        if( ret > 0 ){
		std::cout <<"recvfrom "<< inet_ntoa(addr.sin_addr) <<": "<< ntohs( addr.sin_port )<< recvBuff << std::endl;

		if( recvBuff[0] == 'a' && recvBuff[1] == 'b' && recvBuff[2] == 'c' && recvBuff[3] == 'd' ){
			std::string addr_ip = inet_ntoa( addr.sin_addr );
                        int addr_port = ntohs( addr.sin_port );
                        std::cout<<"addr ip: "<<addr_ip<<std::endl;
                        std::cout<<"addr port: "<<addr_port<<std::endl;
			//for(  )
			destInfoMap.insert( std::make_pair( addr_port, addr_ip ) );
		}
        }
	else std::cout<<"receive failed ..."<<std::endl;
       
}


}

#endif










