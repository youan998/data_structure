``` mermaid
graph LR
    %% 1. 上层主干
    S((S)) --> A((A))
    A --> D((D))
    D --> T((T))
    
    %% 2. 中层主干
    S --> B((B))
    B --> E((E))
    E --> T
    
    %% 3. 下层主干
    S --> C((C))
    C --> F((F))
    F --> T
    
    %% 4. 层与层之间的交叉连线（由左向右）
    A --> E
    B --> D
    B --> F
    C --> E
    
    %% 5. 垂直方向的级联
    D --> E
    E --> F
    
    %% 6. 回环连线（逆向）
    F --> D

    classDef default fill:#656c8e, stroke:#fff, stroke-width:2px, color:#fff;
    classDef orange fill:#cf7539, stroke:#fff, stroke-width:2px, color:#fff;
    class T orange;
```
