#include "sensors/Ears.h"

#include <cmath>
#include <cstdlib>
#include "core/Environment.h"    // 路径按你的工程结构调一下

// 工具函数：在 [minVal, maxVal] 区间内生成均匀随机数
static double uniformDouble(double minVal, double maxVal)
{
    double r = static_cast<double>(std::rand()) / RAND_MAX; // [0,1]
    return minVal + r * (maxVal - minVal);
}

Ears::Ears(IBestiole* b)
    : ISensor(b)
{
    // 从环境中读取耳朵的配置
    const SensorConfig& cfg = Environment::getEarConfig();

    // 距离上下限
    deltaMin = cfg.deltaMin;
    deltaMax = cfg.deltaMax;

    // γ 在 [gammaMin, gammaMax] 内随机
    gamma = uniformDouble(cfg.gammaMin, cfg.gammaMax);
}

void Ears::draw(UImg& img)
{
    // 先画内部 bestiole（以及其它装饰器）
    Decorator::draw(img);

    // 再在身体两侧画两个“小耳朵”
    int cx = getX();
    int cy = getY();
    double theta = getOrientation();   // 朝向（弧度）

    // 耳朵相对中心的偏移距离
    double r = getSize() * 0.5;

    // 利用朝向 ±90° 方向，计算左右耳位置
    double thetaLeft  = theta + M_PI_2;
    double thetaRight = theta - M_PI_2;

    int earLX = static_cast<int>(cx + std::cos(thetaLeft)  * r);
    int earLY = static_cast<int>(cy - std::sin(thetaLeft)  * r);
    int earRX = static_cast<int>(cx + std::cos(thetaRight) * r);
    int earRY = static_cast<int>(cy - std::sin(thetaRight) * r);

    // 耳朵颜色可以用和身体一样的颜色，或固定颜色
    T earColor[3] = { 0, 0, 0 };  // 黑色小耳朵
    img.draw_circle(earLX, earLY, 2, earColor);
    img.draw_circle(earRX, earRY, 2, earColor);
}

bool Ears::canSee(const IBestiole& b) const
{
    // ==== 1) 距离判定：在 [deltaMin, deltaMax] ====
    double x1 = static_cast<double>(getX());
    double y1 = static_cast<double>(getY());
    double x2 = static_cast<double>(b.getX());
    double y2 = static_cast<double>(b.getY());

    double dx = x2 - x1;
    double dy = y1 - y2;  // 屏幕坐标：y 向下为正，所以用 y1 - y2

    double dist = std::sqrt(dx * dx + dy * dy);
    if (dist < deltaMin || dist > deltaMax)
        return false;

    // ==== 2) 听觉是 360°，不做视角判定 ====

    // ==== 3) 伪装判定：γ > ψ 才能“听到/检测到” ====
    double psi = b.getCamouflage();    // 目标伪装能力 ψ
    if (gamma <= psi)
        return false;

    return true;
}
