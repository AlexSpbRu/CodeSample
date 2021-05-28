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

//		����������� ������� ����������� � ����

class CFutballPitch : public CFutballEntity {
	CFutballPitch() = delete;
	~CFutballPitch() = delete;
	//  �������� �������������� �������������� ���� � ����������� �� ������� ���� � �����
public :
};


class CGameParticipant;
//   ������� ����� ���������

class CModel {
public:
	virtual bool	Calculate( CGameParticipant& participant) = 0;
};


//	������ ��������� ���� �� ����

class CBallModel : public CModel {
public:
	bool	Calculate( CGameParticipant& participant) override;
};


//		������ ��������� ������ � ���������� ������ �����������. ������� ������� ����������� 
//      � ��������� ������, ����������� �� ��� �������������� ���������������.


//  ������� ����� ��� ����������� �������� ����� ����� � ������ 
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

//   ����� ������ ������ ��������� �����

class CRefereeModel : public CModel {

};

//   ������ ��������� ����� � ����

class CFieldRefereeModel : public CRefereeModel {
public:
	bool	Calculate( CGameParticipant& participant) override;
};
};

//   ������ ��������� ����� �� �����

class CLineRefereeModel : public CRefereeModel {
public:
	bool	Calculate( CGameParticipant& participant) override;
};
};



//		��������� ������� ����������� � ���� - ���, ������ � �����.

class CGameParticipant : public CFutballEntity {
protected:
	CModel* model;
	float	speed;  //  �������� � ����������� ��������
	float	angle;
public:
	void	setSpeed(float );
	void	setAngle(float );
	//
	float	getSpeed();  
	float	getAngle();
	//
	float 
	void	SetDirection( float Angle);    //  ������� ����������� �������� ���� �� CAI (������������ ���������) ���� �� ������
	void	Run(double dTime);			//		����������� �� ���������� ������� dTime
};

//      ������
class CFootballer : public CGameParticipant {
	CFootballer() = delete;
	~CFootballer() = delete;
protected :
	bool	controlled;         //   ������� ����, ��� ����������� ��������� �����
	float	defence_skill;		//   ���������� ����������
	float	attack_skill;
	float	dribbling_skill;
	float	hitting_force;		//  ���� � �������� �����
	float	hitting_accuracy;
public:
	
};


//      �����
class CReferee : public CGameParticipant {
	CReferee() = delete;
	~CReferee() = delete;
protected:
	float	max_speed;			//   ��������������� ��������������: ������������ �������� � ������������
	float	endurance;

public:
};


//  ��� � ����

class CBall : public CGameParticipant {
	CBall() = delete;
	~CBall() = delete;
public:
};


//		������������� ����

//    ������� �� AI ��� ����������� � ���� ��������� ( ������, ����� � ��� (? ��������) )

 enum class ECommand {};

struct CCommand {
	CGameParticipant&	participant;
	ECommand			command;
	float				direction;
	// ... ��� �������������� ����������
};

//		������������ ��������� - ������� ����� �������� �������� ��������� ������� ��������

class CAI {
public:
	 std::vector<CCommand>  AIAlorithm();
	 virtual std::vector<CCommand> SituationAnalysis(const std::vector<std::shared_ptr<CFootballer>>& Footballers) = 0;   //		������ �������� �� ����
};

//		������������ ��������� ��� ���������� �������� � �������

class CAITeam : public CAI {
public :
	std::vector<CCommand>  SituationAnalysis( const std::vector<std::shared_ptr<CFootballer>>& Footballers ) override;   //		������ �������� �� ����
	void SetCommand( const std::vector<CCommand>& commands );   //		���������� �������� ������� 
};


//		������������ ��������� ��� ���������� �������
class CAIReferee : public CAI {
public:
	std::vector<CCommand>  SituationAnalysis(const std::vector<std::shared_ptr<CFootballer>>& Footballers) override;   //		������ �������� �� ����
	void SetCommand(const std::vector<CCommand>& commands);   //		���������� �������
};


//		���������� �������

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




//    ��������� ����� ��������� ���������� ���� � ��������� ���������������� (+/- ������������� ���������� )
//    � ���������������� �������� ���������. 
//		�������� �������� �������� ������� � �������� ����������� � � ������������� ������������
//	  ��� ���������� ��������� �������
//		���������� � ������ (����������) � �������

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
	//		�������� ����������� 
	std::shared_ptr<CFootballer> CreateGoalkeeper();
	std::shared_ptr<CFootballer> CreateForward();
	std::shared_ptr<CFootballer> CreateDefender();
	std::shared_ptr<CFootballer> CreateGoalkeeper();
	std::shared_ptr<CFootballer> CreateHalfDefender();
	//		�������� ������� 
	std::vector<std::shared_ptr<CFootballer>>	CreateTeam();
	//		�������� �����
	std::shared_ptr<CReferee>				CreateFieldReferee();
	std::shared_ptr<CReferee>				CreateLineReferee();
	std::vector<std::shared_ptr<CReferee>>	CreateReferee();
	//		�������� ����
	std::shared_ptr<CFutballPitch>			CreateFutballPitch();
};


//   ����� ����������� ��������� ���� : 
//		- �������� � ������������� ��������, ������ � �����
//		- ���������� ����� �����������

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
	// ����� ������ ����������
	void	ChooseTeam(const std::stringbuf& TeamName);
	void	ChooseOpponentTeam(const std::stringbuf& TeamName);
	// ����� ��������
	void	ChooseStadium(const std::stringbuf& StadiumName);
	//  ������������� ���� ����������� ���� �� ���������� �� �����
	void	Init(const std::stringbuf& FileName);
	//	������ �������� �����
	bool	Run(); 
	//   �������� ���� �������� (����� � ����������� )
	void	DestroyAll();
};