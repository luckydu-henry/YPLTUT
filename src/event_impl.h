#pragma once
#include <plat/event.hpp>
#include <queue>
// 这个宏可以直接将子结构体需要的内容复制到内部
// 变量名在所有平台下是一致的
#define CRS_INHERITAGE_EVENT_IMPL                \
    struct {                                     \
        std::queue<crs::plat::wevent>  m_events; \
    }
// 这个宏可以以内联模式复制粘贴父类代码
// 实现接口的继承功能但是用一种独特的方式
#define CRS_PLAT_EVENT_IMPL_PUSH_EVENT(Event) \
    m_events.push(Event)
// m_process_events 方法是所有子类都必须定义的
#define CRS_PLAT_EVENT_IMPL_POP_EVENT(Event, bblock)\
    if (m_events.empty()) {             \
        m_process_events();             \
        if (bblock) {                   \
            while (m_events.empty()) {  \
                m_process_events();     \
            }                           \
        }                               \
    }                                   \
    if (!m_events.empty()) {            \
        Event = m_events.front();       \
        m_events.pop();                 \
                                        \
        return true;                    \
    }                                   \
    return false                        