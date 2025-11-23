#include "sensors/Eyes.h"
#include "core/Environment.h"
//#include "../core/Bestiole.h"

#include <cmath>
#include <cstdlib>


// 小工具函数：在 [min, max] 范围内取均匀随机数
static double uniformDouble(double minVal, double maxVal)
{
    double r = static_cast<double>(std::rand()) / RAND_MAX; // [0,1]
    return minVal + r * (maxVal - minVal);
}

Eyes::Eyes(IBestiole* b)
    : ISensor(b)
{
    // 从环境配置中读取眼睛参数区间
    const SensorConfig& cfg = Environment::getEyeConfig();

    // 距离上下限直接拿配置
    deltaMin = cfg.deltaMin;
    deltaMax = cfg.deltaMax;

    // 视场角 alpha 在 [alphaMin, alphaMax] 内随机
    // ⚠ 假设 Environment 中存的是“度数”，这里转为弧度
    double alphaDeg = uniformDouble(cfg.alphaMin, cfg.alphaMax);
    alpha = alphaDeg * std::acos(-1.0) / 180.0;

    // 检测能力 γ 在 [gammaMin, gammaMax] 内随机
    gamma = uniformDouble(cfg.gammaMin, cfg.gammaMax);
};

void Eyes::draw(UImg& img)
{
    // 先让内部 bestiole（以及其它装饰器）画自己的东西
    ISensor::draw(img);

    // 再在前方画一个小圆点作为“眼睛”
    int cx = getX();
    int cy = getY();
    double theta = getOrientation(); // 弧度

    // 眼睛位置：从中心沿朝向方向偏移一点
    double r = m_bestiole->getSize() * 0.4;   // 使用被装饰的 bestiole 的公开尺寸
    int eyeX = static_cast<int>(cx + std::cos(theta) * r);
    int eyeY = static_cast<int>(cy - std::sin(theta) * r); // 注意 y 轴朝下

    unsigned char eyeColor[3] = { 255, 255, 255 }; // 白色眼睛
    img.draw_circle(eyeX, eyeY, 2, eyeColor);
}

bool Eyes::canSee(const IBestiole& b) const
{
    // 1) 距离判定：在 [deltaMin, deltaMax] 范围内
    double x1 = static_cast<double>(getX());
    double y1 = static_cast<double>(getY());
    double x2 = static_cast<double>(b.getX());
    double y2 = static_cast<double>(b.getY());

    double dx = x2 - x1;
    double dy = y1 - y2;  // 屏幕坐标系 y 向下为正，所以这里是 y1 - y2
    double dist = std::sqrt(dx * dx + dy * dy);

    if (dist < deltaMin || dist > deltaMax)
        return false;

    // 2) 视角判定：是否在前方扇形内
    double theta    = getOrientation();        // 我的朝向
    double angleToB = std::atan2(dy, dx);      // 指向目标的方向

    // 归一化角差到 [-π, π]
    double dTheta = std::atan2(std::sin(angleToB - theta),
                               std::cos(angleToB - theta));

    if (std::fabs(dTheta) > alpha * 0.5)
        return false;

    // 3) 伪装判定：γ > ψ 才能看到
    double psi = b.getOpacity();   // 使用目标的透明度/伪装近似值（IBestiole 提供 getOpacity）
    if (gamma <= psi)
        return false;

    return true;
}
