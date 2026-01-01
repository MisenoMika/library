# War Thunder AIR


## 1. 操作说明
### 1.1 移动（WASD）
- `w`：向上移动
- `s`：向下移动
- `a`：向左移动
- `d`：向右移动

### 1.2 攻击
- `↑`：发射 **导弹 Missile**（玩家导弹 AI=2，会自动追踪敌人；不追 Bomber）
- `↓`：发射 **炮弹 Shell**（玩家炮弹 AI=2，直线飞行）
- `←`：触发“侧向连发/散射”模式（根据当前朝向决定侧射方向）
- `→`：触发“侧向连发/散射”模式（同上）



### 1.3 退出
- `q` / `Q`：直接退出游戏循环（Game::update 中处理）

### 1.4 死亡后重开
Game Over 界面：
- `Y`：重新开始
- `N` / `Q`：退出

---

## 2. 资源与道具
### 2.1 金币 Coins
- 击毁敌人会掉金币
- 当金币 `>= 500` 时，玩家会**自动升级**一次，同时游戏**进入下一关**

### 2.2 道具（Item）
地图会周期性生成两类拾取物，玩家靠近（距离 ≤ 2）自动拾取：
- **MedicalPack `[+]`**：+100 生命
- **WeaponPack `[W]`**：+50 炮弹、+10 导弹

---

## 3. EnemyShip

### 3.1 GunBoat（小艇）
- 血量：20
- 特点：移动较随机；与玩家在同一行/列时会直线开火（Shell）
- 击毁奖励：+10 Coins

### 3.2 Destroyer（驱逐舰）
- 血量：40
- 特点：更积极追踪玩家；会发射炮弹（对齐时）并周期性发射鱼雷（Torpedo）
- 击毁奖励：+30 Coins

### 3.3 Cruiser（巡洋舰）
- 血量：90
- 特点：水平移动，会定时四向开火（上下左右 Shell），并周期性发射导弹（Missile，AI=1 追玩家）
- 击毁奖励：+50 Coins

### 3.4 Bomber（轰炸机/空袭单位）
- 血量：**99999（Be designed as an unkillable unit）**
- 特点：从上方区域横向巡航；会投放鱼雷（Torpedo，目标随机 Y）并周期性散射三发炮弹（Shell）


---
## 4.武器
- Shell
- Torpedo
- Missile

## 5. 升级与成长（玩家）
玩家升级触发条件：
- `coins >= 500` 时自动升级一次

升级效果（`PlayerShip::levelUp()`）：
- 回复生命： +200
- 最大生命（maxHealth）：每 **2 级** +200
- 炮弹：+100
- 导弹：+10
- 经过一定时间会自动恢复子弹和血量
- Level 2:解锁散射侧弦炮（随等级up，发出散射炮弹概率up）
- Level 4:解锁散射前炮
---

## 6. How enemies get more powerful as Level ↑↑
主要体现在**更多敌人**与**更智能的导弹**


### 6.1More Enemy

- **GunBoat 最大数量**
  - `maxGunBoatCount = level + 2`

- **Bomber 最大数量**
  - `maxBomberCount = (level + 1) / 3 + 1`
  - 大约每 3 级增加 1 架

- **Destroyer 最大数量**
  - `maxDestroyerCount = level + 1`

- **Cruiser 最大数量**
  - `maxCruiserCount = (level / 2) + 1`
  - 大约每 2 级增加 1 艘

- **MedicalPack / WeaponPack 最大数量**
  - `maxMedicalPackCount = 2 + (level / 3)`
  - `maxWeaponPackCount  = 2 + (level / 3)`
  - 等级越高，道具“上限”也略提高（但仍受生成周期限制）

这意味着：**玩家每升一级，战场能同时存在的敌人总体规模会变大**，并且中后期更容易出现 Destroyer / Cruiser 等更强单位的组合压力。

### 6.2 敌人的“命中/追踪难度”随 Level 变化（导弹 AI）
敌方导弹（`Missile`，AI=1）追踪玩家时有一个“保持旧方向”的概率：
```cpp
if(rand() % 100 < (85 - 5*game->getLevel()) && (oldDx != 0 || oldDy != 0)) {
    dx = oldDx;
    dy = oldDy;
}
```
含义（直观解释）：
- `level` 越高，`(85 - 5*level)` 越低
- 这个分支触发概率降低 → 导弹越不“犹豫”，越倾向于**根据玩家当前位置更新方向**
- 所以在更高等级下，敌方导弹总体上会表现得更“聪明/更追人”（更难躲）

> 注意：当等级足够高时该值可能变为负数，意味着这个“保持旧方向”的分支几乎不会触发，导弹将更频繁修正方向。



---


