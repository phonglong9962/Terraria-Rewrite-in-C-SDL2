#include "LoadingState.h"

Distributor *Distributor::instance = nullptr;
Camera *Camera::instance = nullptr;

LoadingState::LoadingState(int type)
{
	id = 2;
	loadingType = type;
	Window::get()->doneLoading = false;
}

// Init functions
void initAllComponent()
{
	Distributor::get()->registerComponent<Input>();
	Distributor::get()->registerComponent<PlayerTag>();
	Distributor::get()->registerComponent<Transform>();
	Distributor::get()->registerComponent<RenderAble>();
	Distributor::get()->registerComponent<CameraTracking>();
	Distributor::get()->registerComponent<RigidBody>();
}

void initAllSystem()
{
	Distributor::get()->registerSystem<InputSystem>();
	Distributor::get()->registerSystem<MovementSystem>();
	Distributor::get()->registerSystem<CameraTrackingSystem>();
	Distributor::get()->registerSystem<PhysicsSystem>();
	Distributor::get()->registerSystem<RenderSystem>();

	Signature signatureInputSystem;
	signatureInputSystem.set(Distributor::get()->getComponentType<Input>());
	signatureInputSystem.set(Distributor::get()->getComponentType<Transform>());
	Distributor::get()->setSystemSignature<InputSystem>(signatureInputSystem);

	Signature signatureMovementSystem;
	signatureMovementSystem.set(Distributor::get()->getComponentType<Transform>());
	Distributor::get()->setSystemSignature<MovementSystem>(signatureMovementSystem);

	Signature signatureCameraTrackingSystem;
	signatureCameraTrackingSystem.set(Distributor::get()->getComponentType<CameraTracking>());
	signatureCameraTrackingSystem.set(Distributor::get()->getComponentType<Transform>());
	Distributor::get()->setSystemSignature<CameraTrackingSystem>(signatureCameraTrackingSystem);

	Signature signaturePhysicsSystem;
	signaturePhysicsSystem.set(Distributor::get()->getComponentType<Transform>());
	signaturePhysicsSystem.set(Distributor::get()->getComponentType<RigidBody>());
	Distributor::get()->setSystemSignature<PhysicsSystem>(signaturePhysicsSystem);

	Signature signatureRenderSystem;
	signatureRenderSystem.set(Distributor::get()->getComponentType<Transform>());
	signatureRenderSystem.set(Distributor::get()->getComponentType<RenderAble>());
	Distributor::get()->setSystemSignature<RenderSystem>(signatureRenderSystem);
}

void loadingType0()
{
	WorldHandle::get()->loadWorld("map");
	WorldHandle::get()->pullTexture();
	Distributor::get()->init();

	initAllComponent();
	initAllSystem();

	PlayerTag ptag;
	ptag.isAlive = true;
	ptag.isArmorBody = true;
	ptag.isArmorHead = true;
	ptag.isArmorLegs = true;
	ptag.meleeSpeed = 2.0f;

	Entity e = Distributor::get()->createEntity();
	Distributor::get()->addComponent(e, Input{});
	Distributor::get()->addComponent(e, ptag);
	Distributor::get()->addComponent(e, RigidBody { Vector2<char>(38, 54) });
	Distributor::get()->addComponent(e, CameraTracking{true});
	Distributor::get()->addComponent(e, Transform{ {}, Vector4<float>(0.15f, 0.15f, 2, 2), 
		Vector2<float>(float(WorldHandle::get()->getWorldWidth() / 2), 200), 0, false, 0, -1 });
	Distributor::get()->addComponent(e, RenderAble{ RENDERING_TYPE_PLAYER, NULL, Vector2<int>(38, 54), {} });
	Distributor::get()->refreshEntityInAllSystem(e);

	GraphicsHandle::get()->loadSprite(TEXTURE_TYPE_FREED, BODY_TEXTURE, "assets/Player_1_8.png");
	GraphicsHandle::get()->loadSprite(TEXTURE_TYPE_FREED, HEAD_TEXTURE, "assets/Player_0_0.png");
	GraphicsHandle::get()->loadSprite(TEXTURE_TYPE_FREED, LEGS_TEXTURE, "assets/Player_0_11.png");
	GraphicsHandle::get()->loadSprite(TEXTURE_TYPE_FREED, EYE1_TEXTURE, "assets/Player_0_1.png");
	GraphicsHandle::get()->loadSprite(TEXTURE_TYPE_FREED, EYE2_TEXTURE, "assets/Player_0_2.png");
	GraphicsHandle::get()->loadSprite(TEXTURE_TYPE_FREED, HAIR_TEXTURE, "assets/Player_Hair_1.png");
	GraphicsHandle::get()->loadSprite(TEXTURE_TYPE_FREED, ARMS_TEXTURE, "assets/Player_4_7.png");
	GraphicsHandle::get()->loadSprite(TEXTURE_TYPE_FREED, SHOES_TEXTURE, "assets/Player_0_12.png");

	GraphicsHandle::get()->loadSprite(TEXTURE_TYPE_FREED, ARMOR_BODY_TEXTURE, "assets/Armor/Armor_190.png");
	GraphicsHandle::get()->loadSprite(TEXTURE_TYPE_FREED, ARMOR_HEAD_TEXTURE, "assets/Armor_Head_189.png");
	GraphicsHandle::get()->loadSprite(TEXTURE_TYPE_FREED, ARMOR_LEGS_TEXTURE, "assets/Armor_Legs_130.png");

	GraphicsHandle::get()->loadSprite(TEXTURE_TYPE_NPC, SLIME_TEXTURE, "assets/NPC_1.png");
	GraphicsHandle::get()->loadSprite(TEXTURE_TYPE_NPC, MUMMY_TEXTURE, "assets/NPC_78.png");
	GraphicsHandle::get()->loadSprite(TEXTURE_TYPE_NPC, DARK_MUMMY_TEXTURE, "assets/NPC_79.png");
	GraphicsHandle::get()->loadSprite(TEXTURE_TYPE_NPC, BLOOD_MUMMY_TEXTURE, "assets/NPC_80.png");
	GraphicsHandle::get()->loadSprite(TEXTURE_TYPE_NPC, FROZEN_ZOMBIE_ARM, "assets/NPC_431.png");
}

void loadingType1()
{
	WorldHandle::get()->createWorld("map", 4200, 1200);
}

int threadFunction(void* data)
{
	switch ((int)data)
	{
	case 0:
		loadingType0();
		break;
	case 1:
		loadingType1();
		break;
	default:break;
	}

	// Done initializing
	return Window::get()->doneLoading = true;
}

void LoadingState::init()
{
	loadingThread = SDL_CreateThread(threadFunction, "Loading Thread", (void*)loadingType);
	SDL_DetachThread(loadingThread);
	GraphicsHandle::get()->loadSprite(TEXTURE_TYPE_FREED, BACKGROUND_TEXTURE, "assets/SplashScreens/Splash_1_0.png");
}

void LoadingState::initInternal()
{
	std::cout << "LoadingState Initializing!" << std::endl;
	SDL_SetRenderDrawColor(Window::get()->getRenderer(), 128, 128, 128, 255);
	init();
}

void LoadingState::update()
{
	GraphicsHandle::get()->showSprite(TEXTURE_TYPE_FREED, BACKGROUND_TEXTURE);
	if (Window::get()->doneLoading)
	{
		Window::get()->doneLoading = false;
		GraphicsHandle::get()->cleanSprite(TEXTURE_TYPE_FREED, BACKGROUND_TEXTURE);

		switch (loadingType)
		{
		case 0:
			Window::get()->changeState(new PlayState());
			break;
		case 1:
			Window::get()->changeState(new MenuState());
			break;
		default:break;
		}
	}
}

void LoadingState::updateInternal()
{
	update();
}