#include "Main.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

//Variables globales-------------------------
const unsigned short PORT = 5000;
const string IPADDRESS("127.0.0.1");
string msg_send;
bool quit = false;
sf::TcpSocket socket;
sf::Mutex global_mutex;

//Funciones-------------------------
void DoStuff();
void Server();
bool Client();
void GetInput();


//-------------------------------------------------
int main(int argc, char* argv[])
{
	sf::Thread* thread = 0;
	char answer;

	cout << "\t\t\t\t\t--Bienvenido al chat de KrigerFS--";
	cout << "\n\t\t\t\t\t\t--Selecciona-- \nServer -> (S)\n  \nCliente -> (C)\n" << endl;
	cout << "-> ";
	cin >> answer;

	if (answer != toupper(answer))//Condición para checar si el input es mayusucula
	{
		answer = toupper(answer);
		if (answer == 'S' || answer == 'C')
		{
			if (answer == 'S') { Server(); }
			if (answer == 'C') { Client(); }
		}
		else
		{
			return -1;
		}
	}
	if (answer == 'S' || answer == 'C')
	{
		if (answer == 'S')//Conexión de server
		{
			Server();
		}
		else if (answer == 'C')//Conexión de cliente
		{
			Client();
		}
	}
	else
	{
		return -1;
	}

	thread = new sf::Thread(&DoStuff);
	thread->launch();

	while (!quit)
	{
		GetInput();
	}
	if (thread)
	{
		thread->wait();
		delete thread;
	}
	return 0;
}

//-------------------------------------------------
void DoStuff()
{
	string old_msg;
	while (!quit)
	{
		sf::Packet packet_send;
		sf::Packet packet_receive;
		string msg;

		global_mutex.lock();
		packet_send << msg_send;

		global_mutex.unlock();
		socket.send(packet_send);

		socket.receive(packet_receive);

		if ((packet_receive >> msg) && old_msg != msg && !msg.empty())
		{
			cout << msg << endl;
			old_msg = msg;
		}
	}
}

//-------------------------------------------------
void Server()
{
	sf::TcpListener listener;

	listener.listen(PORT);
	listener.accept(socket);

	cout << "\n\nDireccion IP del cliente conectado - - > " << socket.getRemoteAddress() << endl;
}

//-------------------------------------------------
bool Client()
{
	if (socket.connect(IPADDRESS, PORT) == sf::Socket::Done)
	{
		system("cls");
		cout << "\t\t\t\t\t--Bienvenido al chat de KrigerFS--\n";
		cout << "\n\t\t\t\t\t---> Ingresa 'exit' para salir <---" << endl;
		cout << "\nSTATUS - - > Conectado\n";
		return true;
	}
	else
	{
		return false;
	}
}

//-------------------------------------------------
void GetInput()
{
	string message;

	cout << " Mensaje - - > ";
	getline(cin, message);

	if (message == "exit")//Condición de salida
	{
		quit = true;
	}
	else
	{
		global_mutex.lock();
		msg_send = message;
		global_mutex.unlock();
	}
}

/*
Game::Game() : mWindow(sf::VideoMode(800, 800), "SFML Application"), mPlayer()
{
	mPlayer.setRadius(40.f);
	mPlayer.setPosition(100.f, 100.f);
	mPlayer.setFillColor(sf::Color::Cyan);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;
			case sf::Event::Closed:
				mWindow.close();
				break;
		}
	}
}

void Game::update(sf::Time _deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);

	if (mIsMovingUp)
	{
		movement.y -= PlayerSpeed;
	}
	if (mIsMovingDown)
	{
		movement.y += PlayerSpeed;
	}
	if (mIsMovingLeft)
	{
		movement.x -= PlayerSpeed;
	}
	if (mIsMovingRight)
	{
		movement.x += PlayerSpeed;
	}
	mPlayer.move(movement * _deltaTime.asSeconds());
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key _key, bool _isPressed)
{
	if (_key == sf::Keyboard::W)
	{
		mIsMovingUp = _isPressed;
	}
	else if (_key == sf::Keyboard::S)
	{
		mIsMovingDown = _isPressed;
	}
	else if (_key == sf::Keyboard::A)
	{
		mIsMovingLeft = _isPressed;
	}
	else if (_key == sf::Keyboard::D)
	{
		mIsMovingRight = _isPressed;
	}
}
*/

/*
void start_chat(char _answer)
{
	if (_answer == 'C')
	{
		sf::TcpSocket tcp_socket;
		tcp_socket.connect("127.0.0.1", 45000);
		const int msg_size = 100;
		char message[msg_size] = "Hola que tal ;D";

		tcp_socket.send(message, msg_size);
	}
	else if (_answer == 'S')
	{
		sf::TcpListener listener;
		listener.listen(45000);

		sf::TcpSocket socket;
		if (listener.accept(socket) != sf::Socket::Done)
		{
			return -1;
		}
		else
		{
			sf::sleep(sf::seconds(1));

			const size_t size = 100;
			char data[size];
			size_t read_size;
			if (socket.receive(data, size, read_size) != sf::Socket::Done)
			{
				return -1;
			}
			cout << data << endl;
		}
	}
	else
	{
		cout << "\nValor erroneo" << endl;
	}
}
*/