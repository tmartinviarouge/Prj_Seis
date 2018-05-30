//
#include <iostream>
using namespace std;

#include "../defs/c_socket.3.3.h"


//*************************************************
//	class DemonSock
//*************************************************
Demon::Demon()
{
}

//----------------------------------------------
bool Demon::activerDemon()
{
    ActiverThread();
    return true;
}


//*************************************************
//	class RecepteurSock
//*************************************************
Recepteur::Recepteur()
{
}

//----------------------------------------------
bool Recepteur::activerReception()
{
    ActiverThread();
    return true;
}


//*************************************************
//	class _SOCK_THREAD
//*************************************************
_SOCK_THREAD::_SOCK_THREAD()
{
}

//----------------------------------------------
_SOCK_THREAD::~_SOCK_THREAD()
{
    pthread_join (_pthread,NULL);
}

//----------------------------------------------
bool _SOCK_THREAD::activerDemon()
{
    cerr<<"[_SOCK_THREAD::activerDemon()]methode virtuelle, utilisez la classe 'DemonSock'"<<endl;
    return false;
}

//----------------------------------------------
bool _SOCK_THREAD::activerReception()
{
    cerr<<"[_SOCK_THREAD::activerReception()]methode virtuelle, utiliser la classe 'RecepteurSock'"<<endl;
    return false;
}

//----------------------------------------------
void * _SOCK_THREAD::StartStatic(void *todo)
{
	_SOCK_THREAD *monThread = (_SOCK_THREAD *)todo;
	monThread->_Corps();
	pthread_exit(NULL);
}

//----------------------------------------------
void _SOCK_THREAD::ActiverThread()
{
	pthread_create(&_pthread,NULL,StartStatic,this);
}


//*************************************************
//	classe _Socket
//*************************************************

_Socket::_Socket( int localport , int remoteport, string remoteaddr,int nbPlaceAttente, bool M_cast) :
 portLocal(localport) , nbPlacesAttenteDemandeDeConnexion(nbPlaceAttente),MultiCast(M_cast)
{
	codErr = _Socket::PAS_D_ERREUR;
	CoordDistant.sin_family=AF_INET;
	canal=-1;
	CoordDistant.sin_port=htons(remoteport); /* numero de port en format reseau*/
	if (inet_aton(remoteaddr.c_str(), &CoordDistant.sin_addr) == 0){
	  	cerr<<"_Socket::_Socket - adresse distante : Format d'adresse IPv4 incorrecte "<<endl;
		codErr = _Socket::ERR_FORMAT_IPV4;
	}
}

//----------------------------------------------
_Socket::~_Socket ( ) { }

//----------------------------------------------
string _Socket::getAdresseDistante ( )
{ 
	return inet_ntoa(CoordDistant.sin_addr); 
}

//----------------------------------------------
int _Socket::getPortDistant ( )
{ 
	return ntohs(CoordDistant.sin_port); 
}

//----------------------------------------------
bool _Socket::creer_sock(int type, int port,in_addr_t Adrs_Interface, bool exclusif)
{
	SOCKADDR_IN adresse;
	int longueur=sizeof(struct sockaddr_in); /* taille de l'adresse*/
	/* Creation de la socket */
	if ((canal=socket(PF_INET, type, 0))==-1)
	{
		cerr<<"Creation de socket impossible"<<endl;
		codErr = _Socket::ERR_CREATION;
		return  false;
	}
	/* Preparation de l'adresse d'attachement*/
	adresse.sin_family=AF_INET;
	adresse.sin_addr.s_addr=Adrs_Interface;
	adresse.sin_port=htons(port); /* numero de port en format reseau*/

	if (MultiCast){
     		u_int accesLocalMultiple=1;
     		if (exclusif)accesLocalMultiple=0;

     		if (setsockopt(canal,SOL_SOCKET,SO_REUSEADDR,&accesLocalMultiple,sizeof(accesLocalMultiple)) < 0) {
       			cerr<<"echec de modification d'exclusivité de l'accès au port de diffusion "<<getPortLocal()<<endl;
       			return false;
     		}
	};
	/* Demande d'attachement de la socket */
	if(bind(canal,(struct sockaddr*) &adresse, longueur)==-1)
	{
		cerr<<"Attachement de la socket impossible sur port "<<port<<endl;
		close(canal); /* attachement impossible => fermeture de la socket*/
  		canal=-1;
		codErr = _Socket::ERR_BIND;
		return false;
	}
	codErr = _Socket::PAS_D_ERREUR;
	return true;
}

//----------------------------------------------
void _Socket::fermer_socket()
{
	if(canal>-1){
		close(canal);
  		canal=-1;
	}
	codErr = _Socket::PAS_D_ERREUR;
}

//----------------------------------------------
bool _Socket::socket_active()
{
	if(canal>-1){
		return true;
	}
	return false;
}


//*************************************************
//	classe _socketBaseUDP
//*************************************************
_socketBaseUDP::_socketBaseUDP(int localport , string interface, bool M_cast):
 _Socket( localport , 0, "0.0.0.0", 0,M_cast)
{
	if (! M_cast)
		creer_sock(SOCK_DGRAM, localport, inet_addr(interface.c_str()));
}

//------------------------------------------------------------
int _socketBaseUDP::lire(char *datas, int tailleBuffer)
{
	if(canal < 0){
		codErr = _Socket::ERR_CANAL_INVALIDE;
		return codErr;
	};
	int taille;
	taille=sizeof(struct sockaddr_in);
	return recvfrom(canal, datas, tailleBuffer, 0, (struct sockaddr*)&CoordDistant,(socklen_t *)&taille);
}

//------------------------------------------------------------
int _socketBaseUDP::lire(string &chaine)
{
	char datas[TAILLE_BUFFER];
	int nb=lire(datas,TAILLE_BUFFER );
	chaine=" ERREUR DE LECTURE UDP ";
	if (nb>0){
		datas[nb]=0x00;
		chaine=datas;
	};
	return nb;
}

//------------------------------------------------------------
int  _socketBaseUDP::lireDe(char *datas, int tailleBuffer, string & adress, int & port)
{
	int nb=lire(datas, tailleBuffer);
	inet_aton(adress.c_str(), &CoordDistant.sin_addr);
	CoordDistant.sin_port=htons(port);
	return nb;
	
}

//------------------------------------------------------------
int _socketBaseUDP::lireDe(string &chaine,string & adress, int & port)
{
	int nb=lire(chaine);
	inet_aton(adress.c_str(), &CoordDistant.sin_addr);
	CoordDistant.sin_port=htons(port);
	return nb;
}

//*************************************************
//	classe _socketUDP
//*************************************************
_socketUDP::_socketUDP(int localport , string interface):
 _socketBaseUDP( localport , interface, false)

{
	broadcastPossible=0;
}

//------------------------------------------------------------
void _socketUDP::autoriserBroadcast(bool autorisation)
{
	if (autorisation) broadcastPossible=1;
	else broadcastPossible=0;
	setsockopt(canal, SOL_SOCKET, SO_BROADCAST, &broadcastPossible,sizeof(broadcastPossible));
}

//------------------------------------------------------------
int _socketUDP::repondre (char *datas, int taille)
{
	if(canal < 0){
		codErr = _Socket::ERR_CANAL_INVALIDE;
		return codErr;
	};
    	return sendto (canal, datas ,taille, 0,(struct sockaddr*) &CoordDistant, sizeof(sockaddr_in));
}

//------------------------------------------------------------
int _socketUDP::repondre (string chaine)
{
	if(canal < 0){
		codErr = _Socket::ERR_CANAL_INVALIDE;
		return codErr;
	};
    	return sendto (canal, chaine.c_str(),chaine.length(), 0,(struct sockaddr*) &CoordDistant, sizeof(sockaddr_in));
}

//------------------------------------------------------------
int _socketUDP::ecrireA(char *datas, int taille, string adress, int port) 
{
	CoordDistant.sin_port=htons(port);
	if (inet_aton(adress.c_str(), &CoordDistant.sin_addr) == 0){
		codErr = _Socket::ERR_FORMAT_IPV4;
	  	cerr<<"socketClientTcp::seConnecterA - adresse du serveur : Format d'adresse IPv4 incorrecte "<<endl;
		return codErr;
	}
    	return repondre (datas ,taille);
}

//------------------------------------------------------------
int _socketUDP::ecrireA(string chaine,string & adress, int port)
{
	CoordDistant.sin_port=htons(port);
	if (inet_aton(adress.c_str(), &CoordDistant.sin_addr) == 0){
		codErr = _Socket::ERR_FORMAT_IPV4;
	  	cerr<<"socketClientTcp::seConnecterA - adresse du serveur : Format d'adresse IPv4 incorrecte "<<endl;
		return codErr;
	}
	return repondre (chaine);
}

//*************************************************
//	classe _SocketMulticast
//*************************************************
_SocketMulticast::_SocketMulticast(int portDiffusion):
_socketBaseUDP(portDiffusion , "0.0.0.0", true)
{
}

//------------------------------------------------------------
bool _SocketMulticast::sAbonnerAuGroupeMulticast(string AdressseGroupe, bool exclusif , string interface)
{
     struct ip_mreq mreq;

     creer_sock(SOCK_DGRAM, portLocal , inet_addr(interface.c_str()),exclusif);
/*     u_int accesLocalMultiple=1;
     if (exclusif)accesLocalMultiple=0;

     if (setsockopt(canal,SOL_SOCKET,SO_REUSEADDR,&accesLocalMultiple,sizeof(accesLocalMultiple)) < 0) {
       cerr<<"echec de modification d'exclusivité de l'accès au port de diffusion "<<getPortLocal()<<endl;
       return false;
     }
*/
     mreq.imr_multiaddr.s_addr=inet_addr(AdressseGroupe.c_str());
     mreq.imr_interface.s_addr=htonl(INADDR_ANY);
     if (setsockopt(canal,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0) {
	  cerr<<"abonnement au groupe diffusion "<<AdressseGroupe<<" impossible"<<endl;;
	  return false;
     };

     return true;
}

//*************************************************
//	classe SocketRecepteurMulticast
//*************************************************
SocketRecepteurMulticast::SocketRecepteurMulticast(int portDiffusion):
 _SocketMulticast( portDiffusion )
{
}


//*************************************************
//	classe c_socketUDP
//*************************************************
c_socketUDP::c_socketUDP(int localport):
 _socketUDP( localport , STR_ANYADDR)
{
}


//*************************************************
//	classe _socketUDPLo
//*************************************************
c_socketUDPLo::c_socketUDPLo(int localport):
 _socketUDP( localport ,  STR_LOOPBACK)
{
}


//*************************************************
//	classe c_socketTCP
//*************************************************

c_socketTCP::c_socketTCP(  int tmpcanal ,int localport , int remoteport, string remoteaddr , int nbPlaceAttente):
 _Socket( localport , remoteport,  remoteaddr , nbPlaceAttente)
{
	 canal=tmpcanal;
}

//------------------------------------------------------------
int c_socketTCP::lire(char *datas, int taille) 
{
	if(canal < 0){
		codErr = _Socket::ERR_CANAL_INVALIDE;
		return codErr;
	};
        int cmpt = read(canal, datas ,taille);
	return cmpt;
}

//------------------------------------------------------------
int c_socketTCP::lire(string &chaine)
{
	char datas[TAILLE_BUFFER];
	int nb=lire(datas,TAILLE_BUFFER);
	chaine=" ERREUR DE LECTURE TCP ";
	if (nb>0){
		datas[nb]=0x00;
		chaine=datas;
	};
	return nb;
}

//------------------------------------------------------------
int c_socketTCP::ecrire(char *datas, int taille)
{
	if(canal < 0){
		codErr = _Socket::ERR_CANAL_INVALIDE;
		return codErr;
	};
    	return write(canal, datas ,taille);
}

//------------------------------------------------------------
int c_socketTCP::ecrire(string chaine)
{
	return ecrire((char *)chaine.c_str(),chaine.length());
//	return write(canal,chaine.c_str(),chaine.length());
}

//*************************************************
//	classe socketClientTcp
//*************************************************
socketClientTcp::socketClientTcp (int port  ) 
{
	creerSocket( port );
}

//----------------------------------------------
socketClientTcp::~socketClientTcp ( ) { }

//----------------------------------------------
bool socketClientTcp::creerSocket (int port )
{
	portLocal=port;
	return creer_sock(SOCK_STREAM, port, inet_addr(STR_ANYADDR));
}

//----------------------------------------------
bool socketClientTcp::seConnecterA (string adressServeur, int portServeur )
{
	CoordDistant.sin_port=htons(portServeur); /* numero de port en format reseau*/
	if (inet_aton(adressServeur.c_str(), &CoordDistant.sin_addr) == 0){
		codErr = _Socket::ERR_FORMAT_IPV4;
	  	cerr<<"socketClientTcp::seConnecterA - adresse du serveur : Format d'adresse IPv4 incorrecte "<<endl;
		return false;
	}
	//Taille du Handler du Serveur
	int taille = sizeof( struct sockaddr );
	//Test de connexion
	if(connect(canal,(struct sockaddr*)&CoordDistant,taille)==-1){
	  	cerr<<"Echec Connexion au serveur "<<endl;
		codErr = _Socket::ERR_CONNEXION;
		return false;
	};
	return true;
}

//*************************************************
//	classe socketServeurTcp
//*************************************************
socketServeurTcp::socketServeurTcp (int port , int nbPlaceAttente) 
{
	creerSocket ( port ,  nbPlaceAttente );
}

//----------------------------------------------
socketServeurTcp::socketServeurTcp ( ) 
{
}

//----------------------------------------------
socketServeurTcp::~socketServeurTcp ( )
{
}

//----------------------------------------------
bool socketServeurTcp::creerSocket (int port , int nbPlaceAttente )
{
	portLocal=port;
	if(!creer_sock(SOCK_STREAM, port, inet_addr(STR_ANYADDR)))return false;
	if(listen(canal , nbPlaceAttente)==-1){
		codErr = _Socket::ERR_ECOUTE;
		return false;
	}
	return true;
}

//----------------------------------------------
c_socketTCP* socketServeurTcp::accepterDemandeConnexion()
{
	int taille=sizeof(struct sockaddr);
//	struct sockaddr_in Coord;
	int tmpcanal;
        tmpcanal=accept(canal,(struct sockaddr*)&CoordDistant,(socklen_t *)&taille);
        if(tmpcanal<0)	return NULL;
 	c_socketTCP * ptrSockService = new c_socketTCP(tmpcanal,this->portLocal,
					htons(CoordDistant.sin_port),inet_ntoa(CoordDistant.sin_addr));

  	return ptrSockService;
}


//*************************************************
//	classe socketServeurTcpLo
//*************************************************

socketServeurTcpLo ::socketServeurTcpLo (int port , int nbPlaceAttente )
{
	creerSocket ( port ,  nbPlaceAttente );
}

//----------------------------------------------
bool socketServeurTcpLo ::creerSocket (int port , int nbPlaceAttente )
{
	portLocal=port;
	if(!creer_sock(SOCK_STREAM,port,inet_addr(STR_LOOPBACK)))return false;
	if(listen(canal , nbPlaceAttente)==-1){
		codErr = _Socket::ERR_ECOUTE;
		return false;
	}
	return true;
}


//*************************************************
//	classe socketClientTcpLo
//*************************************************
socketClientTcpLo::socketClientTcpLo ( ) {
}

//----------------------------------------------
socketClientTcpLo::~socketClientTcpLo ( ) { }

//----------------------------------------------
bool socketClientTcpLo::creerSocket (int port )
{
	portLocal=port;
	return creer_sock(SOCK_STREAM,port,inet_addr(STR_LOOPBACK));
}

//----------------------------------------------
bool socketClientTcpLo::seConnecterA( int portServeur )
{
	return socketClientTcp::seConnecterA(STR_LOOPBACK,portServeur );
}

//=====================FIN_FICHIER==============================================================

