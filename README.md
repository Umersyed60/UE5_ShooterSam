# 🤖 Shooter Sam (Unreal Engine)

## Overview
A **third‑person sci‑fi shooter** built in Unreal Engine 5.  
The player controls a robot to battle enemy AI robots in a futuristic environment.  
This project was developed as part of my **Unreal learning journey and portfolio expansion**.

## 🎮 Gameplay
- Player robot movement using **Vector2D input values**.
- Customized camera for better shooting focus.
- Shooting mechanics with **line trace bullets** (`LineTraceSingleByChannel`).
- Gun attached to socket, firing particle effects (`UNiagaraFunctionLibrary::SpawnSystemAtLocation`).
- Damage system (`UGameplayStatics::ApplyDamage`) and health components for player & NPCs.
- Health bar HUD for visual cues.

## 🔹 Animation Systems
- Skeletal animations integrated with gameplay.
- **Animation Blueprint** for character logic.
- **Blendspace assets** for smooth transitions between animations.
- **State Machine** for animation flow.
- Additive animations for layered effects.

## 🤖 AI Systems
- **UE5 AI Controller** for custom NPC logic.
- **NavMesh** for AI pathfinding and movement.
- **Behavior Tree + Blackboard** for decision making:
  - RunBehaviorTree, SetValueAsVector
  - Tasks, sequences, selectors, decorators
  - Custom services and tasks
- AI focus and visibility checks:
  - `SetFocus()`, `LineOfSightTo()`, `ClearFocus()`, `ClearValue()`

## 🔊 Audio & Effects
- Ambient background sound using **AmbientSound actor**.
- Gunfire and impact sounds (`UGameplayStatics::PlaySoundAtLocation`).
- Particle effects for bullet impacts.
- Camera shake for immersive feedback.

## 🛠️ Key Unreal Functions Used
- `UGameplayStatics::GetPlayerPawn()` for player reference  
- `UGameplayStatics::GetAllActorsOfClass()` for enemy AI references  
- `CreateWidget()` + `AddToViewport()` for HUD integration  
- `SetPercent()` for health bar updates  

## 🚀 Why This Project Matters
This project strengthened my skills in **Unreal’s animation workflow, AI behavior trees, UI integration, and event-driven programming**, while reinforcing my adaptability across **Unity (8+ years)** and **Unreal (1 year)**.

## ▶️ How to Run
1. Clone the repository.  
2. Open in Unreal Engine 5.x.  
3. Build and run in editor or package for Windows.  
4. Control the player robot, battle AI enemies, and experience the full gameplay loop.  

## 📹 Project Video Link
Watch the gameplay clip on LinkedIn: [Shooter Sam Demo](https://www.linkedin.com/posts/syed-umer-aftab_expanding-my-unreal-portfolio-ive-developed-ugcPost-7490695460760977409-hEFQ/?utm_source=share&utm_medium=member_desktop&rcm=ACoAAC69X2MBd5YEkBw-nbcsGGwhzI8omOUUnsM)

---

