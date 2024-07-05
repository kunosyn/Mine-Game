#pragma once

#pragma region PhysicsConstants
constexpr float GRAVITY = .45f;
#pragma endregion

#pragma region NoiseConstants
constexpr float TERRAIN_FREQUENCY = 1.0f;
constexpr float HEIGHT_MULTIPLIER = 45.0f;
constexpr float HEIGHT_ADDITION = 100.f;
#pragma endregion

#pragma region GameConstants
constexpr int GAME_WIDTH = 800;
constexpr int GAME_HEIGHT = 600;

constexpr int VIEW_WIDTH = 800;
constexpr int VIEW_HEIGHT = 600;

constexpr int RENDER_LOOKBACK = 30;
constexpr int RENDER_LOOK = 30;
#pragma endregion

#pragma region GenerationConstants
constexpr int CHUNK_SIZE = 1250;
constexpr int CHUNK_WIDTH = 25;
constexpr int CHUNK_HEIGHT = 50;

constexpr int MAP_WIDTH = 100000;
constexpr int MAP_HEIGHT = 3000;

constexpr int BLOCK_WIDTH = 20;

constexpr int DIRT_LAYER_HEIGHT = 5;
constexpr float SURFACE_VALUE = 0.25F;
#pragma endregion
