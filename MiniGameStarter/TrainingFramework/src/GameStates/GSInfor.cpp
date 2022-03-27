#include "GSInfor.h"

GSInfor::GSInfor() : GameStateBase(StateType::STATE_INFOR),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_textGameName(nullptr)
{
}
GSInfor::~GSInfor()
{
}
void GSInfor::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu_6.tga");
	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// turn back button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_prev.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->SetName("btn_turnBack");
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});

	m_listButton.push_back(button);

};

void GSInfor::Exit()
{
	ResourceManagers::FreeInstance();
}
void GSInfor::Pause()
{
}
void GSInfor::Resume()
{
}
void GSInfor::HandleEvents()
{
}
void GSInfor::HandleKeyEvents(int key, bool bIsPressed)
{
}
void GSInfor::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}
void GSInfor::HandleMouseMoveEvents(int x, int y)
{
}
void GSInfor::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}
void GSInfor::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		if (it->GetName().compare("btn_volumn") == 0)
		{
			if (GameStateMachine::GetInstance()->isMute())
			{
				it->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_sfx_off.tga"));
			}
			else
				it->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_sfx.tga"));
		}
		it->Draw();
	}
	m_textGameName->Draw();
}
