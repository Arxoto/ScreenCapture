#pragma once

enum class State
{
    /// <summary>
    /// ��ʼ״̬
    /// </summary>
    start = 0,
    /// <summary>
    /// ���ƽ�ͼ����
    /// </summary>
    mask,
    /// <summary>
    /// ���ƹ�����
    /// </summary>
    tool,
    box,
    ellipse,
    arrow,
    number,
    pen,
    line,
    text,
    image,
    mosaic,
    eraser
};
State state = State::start;