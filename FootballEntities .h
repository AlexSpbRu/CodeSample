#pragma once

#include <memory>
#include <vector>

struct SPos {
	float x;
	float y;
};

struct SRect {
	float width;
	float height;
};

class CFutballEntity {
protected :
	SPos		pos;
	SRect		rect;
public :
	SPos		getPos();
	SRect		getRect();
	//
	void		setPos( const SPos& Pos);
	void		setRect( const SRect& Rect);

};

//		Неподвижные объекты участвующие в игре

class CFutballPitch : public CFutballEntity {
	CFutballPitch() = delete;
	~CFutballPitch() = delete;
	//  задаются индивидуальные характеристики поля в зависимости от времени года и суток
public :
};


class CGameParticipant;
//   Базовый класс поведения

class CModel {
public:
	virtual bool	Calculate( CGameParticipant& participant) = 0;
};


//	модель поведения мяча на поле

class CBallModel : public CModel {
public:
	bool	Calculate( CGameParticipant& participant) override;
};


//		Модель поведения игрока с элементами теории вероятности. Веносит элемент случайности 
//      в поведение игрока, основываясь на его индивидуальных характеристиках.


//  базовый класс для футболистов содержит общие члены и методы 
class CFootballerModel : public CModel {

};

class CGoalkeeperModel : public CFootballerModel {
public:
	bool	Calculate( CGameParticipant& participant) override;
};

class CForwardModel : public CFootballerModel {
public:
	bool	Calculate( CGameParticipant& participant) override;
};

class CDefenderModel : public CFootballerModel {
public:
	bool	Calculate( CGameParticipant& participant) override;
};

class CHalfDefenderModel : public CFootballerModel {
public:
	bool	Calculate( CGameParticipant& participant) override;
};

//   Общие детали модели поведения судьи

class CRefereeModel : public CModel {

};

//   Модель поведения судьи в поле

class CFieldRefereeModel : public CRefereeModel {
public:
	bool	Calculate( CGameParticipant& participant) override;
};
};

//   Модель поведения судьи на линии

class CLineRefereeModel : public CRefereeModel {
public:
	bool	Calculate( CGameParticipant& participant) override;
};
};



//		Подвижные объекты участвующие в игре - мяч, игроки и судья.

class CGameParticipant : public CFutballEntity {
protected:
	CModel* model;
	float	speed;  //  скорость и направление движения
	float	angle;
public:
	void	setSpeed(float );
	void	setAngle(float );
	//
	float	getSpeed();  
	float	getAngle();
	//
	float 
	void	SetDirection( float Angle);    //  Задание направления движения либо от CAI (Искуственный интеллект) либо от Игрока
	void	Run(double dTime);			//		перемещение за промежуток времени dTime
};

//      Игроки
class CFootballer : public CGameParticipant {
	CFootballer() = delete;
	~CFootballer() = delete;
protected :
	bool	controlled;         //   признак того, что футболистом управляет Игрок
	float	defence_skill;		//   мастерство футболиста
	float	attack_skill;
	float	dribbling_skill;
	float	hitting_force;		//  сила и точность удара
	float	hitting_accuracy;
public:
	
};


//      Судьи
class CReferee : public CGameParticipant {
	CReferee() = delete;
	~CReferee() = delete;
protected:
	float	max_speed;			//   физиологические характеристики: максимальная скорость и выносливость
	float	endurance;

public:
};


//  Мяч в поле

class CBall : public CGameParticipant {
	CBall() = delete;
	~CBall() = delete;
public:
};


//		Моделирование игры

//    Команда от AI для участвующих в игре сущностей ( игроки, судьи и мяч (? возможно) )

 enum class ECommand {};

struct CCommand {
	CGameParticipant&	participant;
	ECommand			command;
	float				direction;
	// ... ряд дополнительных параметров
};

//		Искуственный интеллект - базовый класс содержит алгоритм обработки игровой ситуации

class CAI {
public:
	 std::vector<CCommand>  AIAlorithm();
	 virtual std::vector<CCommand> SituationAnalysis(const std::vector<std::shared_ptr<CFootballer>>& Footballers) = 0;   //		анализ ситуации на поле
};

//		Искуственный интеллект для управления игроками в команде

class CAITeam : public CAI {
public :
	std::vector<CCommand>  SituationAnalysis( const std::vector<std::shared_ptr<CFootballer>>& Footballers ) override;   //		анализ ситуации на поле
	void SetCommand( const std::vector<CCommand>& commands );   //		управление игроками команды 
};


//		Искуственный интеллект для управления судьями
class CAIReferee : public CAI {
public:
	std::vector<CCommand>  SituationAnalysis(const std::vector<std::shared_ptr<CFootballer>>& Footballers) override;   //		анализ ситуации на поле
	void SetCommand(const std::vector<CCommand>& commands);   //		управление судьями
};


//		футбольная команда

class CFootballTeam {
	CFootballTeam() = delete;
	~CFootballTeam() = delete;
protected:
	friend  CAITeam;
	std::vector<std::shared_ptr<CFootballer>>		footballers;
	CAITeam											AI;
public:
	void	Run(double dTime, const CFootballTeam& Opponent );
};




//    Фабричный класс создающий участников игры с заданными характеристиками (+/- вероятностные отклонения )
//    и соответствующими моделями поведения. 
//		Возможны варианты создания игроков с типовыми параметрами и с индивидуально настроенными
//	  под конкретных известных игроков
//		Аналогично с полями (стадионами) и судьями

class CFootballFabrica {
	CFootballFabrica() = delete;
	~CFootballFabrica() = delete;
	static CFootballFabrica					fabrica;
public :
	friend CFootballer;
	friend CReferee;
	friend CFutballPitch;
	//
	static CFootballFabrica& GetInstance();

	std::shared_ptr<CBall>		CreateBall();
	//		создание футболистов 
	std::shared_ptr<CFootballer> CreateGoalkeeper();
	std::shared_ptr<CFootballer> CreateForward();
	std::shared_ptr<CFootballer> CreateDefender();
	std::shared_ptr<CFootballer> CreateGoalkeeper();
	std::shared_ptr<CFootballer> CreateHalfDefender();
	//		создание команды 
	std::vector<std::shared_ptr<CFootballer>>	CreateTeam();
	//		создание судей
	std::shared_ptr<CReferee>				CreateFieldReferee();
	std::shared_ptr<CReferee>				CreateLineReferee();
	std::vector<std::shared_ptr<CReferee>>	CreateReferee();
	//		создание поля
	std::shared_ptr<CFutballPitch>			CreateFutballPitch();
};


//   класс управляющий процессом игры : 
//		- создание и инициализация стадиона, команд и судей
//		- упарвление всеми персонажами

class CGameplayManager {
	CGameplayManager() = delete;
	~CGameplayManager() = delete;
	static CGameplayManager					manager;

	std::shared_ptr < CFootballTeam >		redTeam;
	std::shared_ptr < CFootballTeam >		whiteTeam;
	std::vector<std::shared_ptr<CReferee>>	referees;
	std::shared_ptr < CFutballPitch >		pitch;

public :
	static CGameplayManager& GetInstance();
	// выбор команд участников
	void	ChooseTeam(const std::stringbuf& TeamName);
	void	ChooseOpponentTeam(const std::stringbuf& TeamName);
	// выбор стадиона
	void	ChooseStadium(const std::stringbuf& StadiumName);
	//  инициализация всех компонентов игры по информации из файла
	void	Init(const std::stringbuf& FileName);
	//	запуск игрового цикла
	bool	Run(); 
	//   удаление всех объектов (вызов в деструкторе )
	void	DestroyAll();
};