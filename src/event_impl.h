#pragma once
#include <plat/event.hpp>
#include <queue>
// ��������ֱ�ӽ��ӽṹ����Ҫ�����ݸ��Ƶ��ڲ�
// ������������ƽ̨����һ�µ�
#define CRS_INHERITAGE_EVENT_IMPL                \
    struct {                                     \
        std::queue<crs::plat::wevent>  m_events; \
    }
// ��������������ģʽ����ճ���������
// ʵ�ֽӿڵļ̳й��ܵ�����һ�ֶ��صķ�ʽ
#define CRS_PLAT_EVENT_IMPL_PUSH_EVENT(Event) \
    m_events.push(Event)
// m_process_events �������������඼���붨���
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