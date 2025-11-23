#ifndef EARS_H
#define EARS_H

#include "../interfaces/ISensor.h"

class Ears : public ISensor
{
private:
    double deltaMin;  // 视距下限
    double deltaMax;  // 视距上限
    // double alpha;     // 本只 bestiole 的视场角（弧度）
    double gamma;     // 本只 bestiole 的检测能力 γ

public:
    // 构造时：从 Environment::eyeConfig 中读取范围，并随机生成 alpha 和 gamma
    explicit Ears(IBestiole* b);

    ~Ears() override = default;

    // 绘制：在基础 bestiole 上画“眼睛”
    void draw(UImg& img) override;

    // 感知：眼睛是否能看到 b
    bool canSee(const IBestiole& b) const override;
};

#endif  // EARS_H