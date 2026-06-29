``` mermaid
graph LR
    %% 1. 预先声明所有节点，锁死上下层级关系
    A((A))
    B((B))
    C((C))
    E((E))
    D((D))
    F((F))
    G((G))

    %% 2. 边缘连线声明
    A --> B
    A --> C
    
    B --> E
    B --> D
    D --> B  
    
    C --> D
    C --> F
    
    %% 【核心修复】先声明 E->G 的长跨度线，再声明 E->D 的短线
    E --> G
    E --> D
    
    D --> G
    F --> G

    %% 3. 样式渲染
    classDef default fill:#656c8e, stroke:#fff, stroke-width:2px, color:#fff;
    classDef orange fill:#cf7539, stroke:#fff, stroke-width:2px, color:#fff;
    class G orange;
```
