``` mermaid
graph LR
    %% 1. 上层主干路径
    A((A)) --> B((B))
    B --> E((E))
    E --> G((G))
    
    %% 2. 下层主干路径
    A --> C((C))
    C --> F((F))
    F --> G((G))
    
    %% 3. 核心节点 D 的汇聚与发散
    B --> D((D))
    C --> D
    E --> D
    D --> G
    
    %% 4. 回环连线（逆向）
    D --> B

    classDef default fill:#656c8e, stroke:#fff, stroke-width:2px, color:#fff;
    classDef orange fill:#cf7539, stroke:#fff, stroke-width:2px, color:#fff;
    class G orange;
```
