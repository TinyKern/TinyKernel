// #ifndef THREAD_H
// #define THREAD_H

// #include <types.h>

// enum DispatchSignalResult
// {
//     Deferred = 0,
//     Yield,
//     Terminate,
//     Continue
// };

// struct SignalActionData
// {
//     uint32 mask   { 0 };
//     int flags       { 0 };
// };

// struct ThreadSpecificData
// {
//     struct ThreadSpecificData* self;
// };

// #define THREAD_PRIORITY_MIN     1
// #define THREAD_PRIORITY_LOW     10
// #define THREAD_PRIORITY_DEFAULT 30
// #define THREAD_PRIORITY_HIGH    50
// #define THREAD_PRIORITY_MAX     99

// #define THREAD_AFFINITY_MASK    0xFFFFFFFF

// struct Thread
// {
//     inline static struct Thread* current()
//     {

//     }
// };

// #endif // THREAD_H