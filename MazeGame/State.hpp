#pragma once

class State
{
public:
	virtual ~State() {};
	
	/*	\opis wczytywanie z dysku tekstur i fontów,
		inicjalizacja obiektów, które mogą zostać wyświetlone i ustalenie ich pozycji na ekranie */
	virtual void init() = 0;
	/* 	\opis obsługa wejścia z klawiatury */
	virtual void handleInput() = 0;
	/*	\opis obsługa zdarzeń takich jak: wciśnięcie przycisku, 
		zmiana stanu obiektu wyświetlanego, zamknięcie okna
		\param dt - czas trwania jednej klatki */ 
	virtual void update(float dt) = 0;
	/*	\opis czyszczenie ekranu, rysowanie obiektów, wyświetlanie ich w oknie aplikacji
		\param dt - czas trwania jednej klatki */ 
	virtual void draw(float dt) = 0;
	/*	\opis wywoływana dla aktualnego stanu w momencie gdy nowy stan jest odkładany na stos
		i nie zastępuje tego stanu */
	virtual void pause() {};
	/*	\opis wywoływana po zdjęciu stanu ze stosu, dla pierwszego elementu z góry */
	virtual void resume() {};
};

