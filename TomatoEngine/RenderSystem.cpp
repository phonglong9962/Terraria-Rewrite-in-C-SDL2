#pragma once

#include "System.h"
#include "GraphicsHandle.h"

void RenderSystem::update()
{
	for (auto &entity : entities)
	{
		auto &transform = Distributor::get()->getComponent<Transform>(entity);
		auto &renderable = Distributor::get()->getComponent<RenderAble>(entity);

		SDL_RendererFlip flip;
		TextureDetails tex;

		int length, index, frameIndex;
		Uint32 time = SDL_GetTicks();

		int vecSpeed = 1 + int(std::abs(transform.velocity.x));

		if (renderable.type == RENDERING_TYPE_PLAYER)
		{
			#pragma region Player Drawing

			auto &playerTag = Distributor::get()->getComponent<PlayerTag>(entity);

			if (!playerTag.isAlive) return;

			float accSpeed = transform.isAttack ? playerTag.meleeSpeed : vecSpeed;
			transform.stillAttack = transform.isAttack ? (transform.stillAttack += 20.0f) : transform.stillAttack;
			flip = transform.direction > 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

			// LEGS
			if (playerTag.isArmorLegs)
			{
				length = transform.action == TEXTURE_IDLE ? 5 : transform.action == TEXTURE_MOVING ? 14 :
					transform.action == TEXTURE_JUMPING ? 1 : -1;
				index = transform.action == TEXTURE_IDLE ? 0 : transform.action == TEXTURE_MOVING ? 6 :
					transform.action == TEXTURE_JUMPING ? 5 : -1;
				frameIndex = (int)(time / (100 / vecSpeed * LEGS_TEXTURE_DELAY)) % length;
				renderable.index.x = 0;
				renderable.index.y = frameIndex + index;
				GraphicsHandle::get()->showSprite(TEXTURE_TYPE_FREED, ARMOR_LEGS_TEXTURE, transform.position, renderable.size, renderable.index, flip);
			}
			else
			{
				length = transform.action == TEXTURE_IDLE ? 5 : transform.action == TEXTURE_MOVING ? 14 :
					transform.action == TEXTURE_JUMPING ? 1 : -1;
				index = transform.action == TEXTURE_IDLE ? 0 : transform.action == TEXTURE_MOVING ? 6 :
					transform.action == TEXTURE_JUMPING ? 5 : -1;
				frameIndex = (int)(time / (100 / vecSpeed * LEGS_TEXTURE_DELAY)) % length;
				renderable.index.x = 0;
				renderable.index.y = frameIndex + index;
				GraphicsHandle::get()->showSprite(TEXTURE_TYPE_FREED, LEGS_TEXTURE, transform.position, renderable.size, renderable.index, flip);
				GraphicsHandle::get()->showSprite(TEXTURE_TYPE_FREED, SHOES_TEXTURE, transform.position, renderable.size, renderable.index, flip);
			}
			bool tag = false;
			if (transform.action == TEXTURE_MOVING &&
				(frameIndex == 1 || frameIndex == 2 || frameIndex == 3 || frameIndex == 8 || frameIndex == 9 || frameIndex == 10))
			{
				tag = true;
			}
			transform.position.y = tag ? transform.position.y -= 2 : transform.position.y;

			if (playerTag.isArmorBody)
			{
				// BODY ASIDE
				renderable.index.y = 1;
				renderable.index.x = 1;
				GraphicsHandle::get()->showSprite(TEXTURE_TYPE_FREED, ARMOR_BODY_TEXTURE, transform.position, renderable.size, renderable.index, flip);
				renderable.index.x = 0;
				GraphicsHandle::get()->showSprite(TEXTURE_TYPE_FREED, ARMOR_BODY_TEXTURE, transform.position, renderable.size, renderable.index, flip);

				// BODY
				length = transform.action == TEXTURE_IDLE ? 1 : transform.action == TEXTURE_MOVING ? 2 :
					transform.action == TEXTURE_JUMPING ? 2 : -1;
				frameIndex = (int)(time / (100 / vecSpeed * BODY_TEXTURE_DELAY)) % length;
				renderable.index.x = frameIndex;
				renderable.index.y = 0;
				GraphicsHandle::get()->showSprite(TEXTURE_TYPE_FREED, ARMOR_BODY_TEXTURE, transform.position, renderable.size, renderable.index, flip);

				// ARM ASIDE
				length = transform.isAttack ? 4 : transform.action == TEXTURE_IDLE ? 1 : transform.action == TEXTURE_MOVING ? 4 :
					transform.action == TEXTURE_JUMPING ? 1 : -1;
				index = transform.isAttack ? 3 : transform.action == TEXTURE_IDLE ? 3 : transform.action == TEXTURE_MOVING ? 3 :
					transform.action == TEXTURE_JUMPING ? 2 : -1;
				renderable.index.y = transform.isAttack ? 2 : transform.action == TEXTURE_IDLE ? 3 :
					transform.action == TEXTURE_MOVING ? 3 : transform.action == TEXTURE_JUMPING ? 3 : -1;
				frameIndex = (int)((transform.isAttack ? transform.stillAttack : time) / (100 / accSpeed * BODY_TEXTURE_DELAY)) % length;
				renderable.index.x = frameIndex + index;
				GraphicsHandle::get()->showSprite(TEXTURE_TYPE_FREED, ARMOR_BODY_TEXTURE, transform.position, renderable.size, renderable.index, flip);
			}
			else
			{
				// BODY ASIDE
				renderable.index.y = 1;
				renderable.index.x = 1;
				GraphicsHandle::get()->showSprite(TEXTURE_TYPE_FREED, BODY_TEXTURE, transform.position, renderable.size, renderable.index, flip);
				renderable.index.x = 0;
				GraphicsHandle::get()->showSprite(TEXTURE_TYPE_FREED, BODY_TEXTURE, transform.position, renderable.size, renderable.index, flip);

				// BODY
				length = transform.action == TEXTURE_IDLE ? 1 : transform.action == TEXTURE_MOVING ? 2 :
					transform.action == TEXTURE_JUMPING ? 2 : -1;
				frameIndex = (int)(time / (100 / vecSpeed * BODY_TEXTURE_DELAY)) % length;
				renderable.index.x = frameIndex;
				renderable.index.y = 0;
				GraphicsHandle::get()->showSprite(TEXTURE_TYPE_FREED, BODY_TEXTURE, transform.position, renderable.size, renderable.index, flip);

				// ARM ASIDE
				length = transform.isAttack ? 4 : transform.action == TEXTURE_IDLE ? 1 : transform.action == TEXTURE_MOVING ? 4 :
					transform.action == TEXTURE_JUMPING ? 1 : -1;
				index = transform.isAttack ? 3 : transform.action == TEXTURE_IDLE ? 3 : transform.action == TEXTURE_MOVING ? 3 :
					transform.action == TEXTURE_JUMPING ? 2 : -1;
				renderable.index.y = transform.isAttack ? 2 : transform.action == TEXTURE_IDLE ? 3 :
					transform.action == TEXTURE_MOVING ? 3 : transform.action == TEXTURE_JUMPING ? 3 : -1;
				frameIndex = (int)((transform.isAttack ? transform.stillAttack : time) / (100 / accSpeed * BODY_TEXTURE_DELAY)) % length;
				renderable.index.x = frameIndex + index;
				GraphicsHandle::get()->showSprite(TEXTURE_TYPE_FREED, ARMS_TEXTURE, transform.position, renderable.size, renderable.index, flip);
			}
			transform.position.y = tag ? transform.position.y += 2 : transform.position.y;

			// HEAD
			if (playerTag.isArmorHead)
			{
				length = transform.action == TEXTURE_IDLE ? 1 : transform.action == TEXTURE_MOVING ? 14 :
					transform.action == TEXTURE_JUMPING ? 1 : -1;
				index = transform.action == TEXTURE_IDLE ? 0 : transform.action == TEXTURE_MOVING ? 6 :
					transform.action == TEXTURE_JUMPING ? 4 : -1;
				frameIndex = (int)(time / (100 / vecSpeed * HEAD_TEXTURE_DELAY)) % length;
				renderable.index.x = 0;
				renderable.index.y = frameIndex + index;
				GraphicsHandle::get()->showSprite(TEXTURE_TYPE_FREED, ARMOR_HEAD_TEXTURE, transform.position, renderable.size, renderable.index, flip);

				length = transform.action == TEXTURE_IDLE ? 1 : transform.action == TEXTURE_MOVING ? 14 :
					transform.action == TEXTURE_JUMPING ? 1 : -1;
				index = transform.action == TEXTURE_IDLE ? 0 : transform.action == TEXTURE_MOVING ? 0 :
					transform.action == TEXTURE_JUMPING ? 0 : -1;
				frameIndex = (int)(time / (100 / vecSpeed * HEAD_TEXTURE_DELAY)) % length;
				renderable.index.x = 0;
				renderable.index.y = frameIndex + index;
				GraphicsHandle::get()->showSprite(TEXTURE_TYPE_FREED, ARMOR_HEAD_TEXTURE, transform.position, renderable.size, renderable.index, flip);
			}
			else
			{
				length = transform.action == TEXTURE_IDLE ? 1 : transform.action == TEXTURE_MOVING ? 14 :
					transform.action == TEXTURE_JUMPING ? 1 : -1;
				index = transform.action == TEXTURE_IDLE ? 0 : transform.action == TEXTURE_MOVING ? 6 :
					transform.action == TEXTURE_JUMPING ? 4 : -1;
				frameIndex = (int)(time / (100 / vecSpeed * HEAD_TEXTURE_DELAY)) % length;
				renderable.index.x = 0;
				renderable.index.y = frameIndex + index;
				GraphicsHandle::get()->showSprite(TEXTURE_TYPE_FREED, HEAD_TEXTURE, transform.position, renderable.size, renderable.index, flip);
				GraphicsHandle::get()->showSprite(TEXTURE_TYPE_FREED, EYE1_TEXTURE, transform.position, renderable.size, renderable.index, flip);
				GraphicsHandle::get()->showSprite(TEXTURE_TYPE_FREED, EYE2_TEXTURE, transform.position, renderable.size, renderable.index, flip);

				length = transform.action == TEXTURE_IDLE ? 1 : transform.action == TEXTURE_MOVING ? 14 :
					transform.action == TEXTURE_JUMPING ? 1 : -1;
				index = transform.action == TEXTURE_IDLE ? 0 : transform.action == TEXTURE_MOVING ? 0 :
					transform.action == TEXTURE_JUMPING ? 0 : -1;
				frameIndex = (int)(time / (100 / vecSpeed * HEAD_TEXTURE_DELAY)) % length;
				renderable.index.x = 0;
				renderable.index.y = frameIndex + index;
				GraphicsHandle::get()->showSprite(TEXTURE_TYPE_FREED, HAIR_TEXTURE, transform.position, renderable.size, renderable.index, flip);
			}

			transform.position.y = tag ? transform.position.y -= 2 : transform.position.y;
			// ARM ACTION
			if (playerTag.isArmorBody)
			{
				length = transform.isAttack ? 4 : transform.action == TEXTURE_IDLE ? 1 : transform.action == TEXTURE_MOVING ? 4 :
					transform.action == TEXTURE_JUMPING ? 1 : -1;
				index = transform.isAttack ? 3 : transform.action == TEXTURE_IDLE ? 3 : transform.action == TEXTURE_MOVING ? 3 :
					transform.action == TEXTURE_JUMPING ? 2 : -1;
				renderable.index.y = transform.isAttack ? 0 : transform.action == TEXTURE_IDLE ? 1 : transform.action == TEXTURE_MOVING ? 1 :
					transform.action == TEXTURE_JUMPING ? 1 : -1;
				frameIndex = (int)((transform.isAttack ? transform.stillAttack : time) / (100 / accSpeed * BODY_TEXTURE_DELAY)) % length;
				renderable.index.x = frameIndex + index;
				GraphicsHandle::get()->showSprite(TEXTURE_TYPE_FREED, ARMOR_BODY_TEXTURE, transform.position, renderable.size, renderable.index, flip);
			}
			else
			{
				length = transform.isAttack ? 4 : transform.action == TEXTURE_IDLE ? 1 : transform.action == TEXTURE_MOVING ? 4 :
					transform.action == TEXTURE_JUMPING ? 1 : -1;
				index = transform.isAttack ? 3 : transform.action == TEXTURE_IDLE ? 3 : transform.action == TEXTURE_MOVING ? 3 :
					transform.action == TEXTURE_JUMPING ? 2 : -1;
				renderable.index.y = transform.isAttack ? 0 : transform.action == TEXTURE_IDLE ? 1 : transform.action == TEXTURE_MOVING ? 1 :
					transform.action == TEXTURE_JUMPING ? 1 : -1;
				frameIndex = (int)((transform.isAttack ? transform.stillAttack : time) / (100 / accSpeed * BODY_TEXTURE_DELAY)) % length;
				renderable.index.x = frameIndex + index;
				GraphicsHandle::get()->showSprite(TEXTURE_TYPE_FREED, ARMS_TEXTURE, transform.position, renderable.size, renderable.index, flip);
			}
			transform.position.y = tag ? transform.position.y += 2 : transform.position.y;
			if (frameIndex + index > length + 1)
			{
				transform.stillAttack = 0;
				transform.isAttack = false;
			}
			#pragma endregion
		}
		else if (RENDERING_TYPE_NPC)
		{
			tex = AssetsPool::get()->getTextureDetails(renderable.spriteId);

			flip = transform.direction < 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

			length = transform.action == TEXTURE_IDLE ? tex.il : transform.action == TEXTURE_MOVING ? tex.ml :
				transform.action == TEXTURE_JUMPING ? tex.jl : transform.action == TEXTURE_ATTACK ? tex.al : -1;
			index = transform.action == TEXTURE_IDLE ? tex.io : transform.action == TEXTURE_MOVING ? tex.mo :
				transform.action == TEXTURE_JUMPING ? tex.jo : transform.action == TEXTURE_ATTACK ? tex.ao : -1;
			frameIndex = (int)(time / (100 / vecSpeed * BODY_TEXTURE_DELAY)) % length;
			renderable.index.x = 0;
			renderable.index.y = frameIndex + index;
			GraphicsHandle::get()->showSprite(TEXTURE_TYPE_NPC, renderable.spriteId, transform.position, renderable.size, renderable.index, flip);
		}
	}
}