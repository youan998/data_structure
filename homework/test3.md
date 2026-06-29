``` mermaid
graph LR
    %% 1. 预先声明所有节点，锁定垂直层级
    S((S))
    A((A))
    B((B))
    C((C))
    D((D))
    E((E))
    F((F))
    T((T))

    %% 2. 初始层
    S --> A
    S --> B
    S --> C

    %% 3. 【核心修复】按“出发节点”逐层向下声明，理顺所有出线口！
    %% -- A 发出的线（上层） --
    A --> D
    A --> E

    %% -- B 发出的线（中层） --
    B --> D
    B --> F

    %% -- C 发出的线（下层） --
    C --> E
    C --> F

    %% -- D 发出的线（上层级联） --
    D --> E  
    D --> T

    %% -- E 发出的线（中层级联） --
    E --> F
    E --> T

    %% -- F 发出的线（下层收束与回环） --
    F --> T
    F --> D  

    %% 4. 样式定义
    classDef default fill:#656c8e, stroke:#fff, stroke-width:2px, color:#fff;
    classDef orange fill:#cf7539, stroke:#fff, stroke-width:2px, color:#fff;
    class T orange;
```
