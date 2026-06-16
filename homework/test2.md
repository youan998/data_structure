``` mermaid
graph LR
    A((A)) --> B((B))
    A --> C((C))
    A --> D((D))
    C --> B
    B --> E((E))
    C --> F((F))
    D --> F
    E --> G((G))
    E --> H((H))
    F --> E
    F --> H
    G --> H
    H --> A

    classDef default fill:#656c8e, stroke:#fff, stroke-width:2px, color:#fff;
    classDef orange fill:#cf7539, stroke:#fff, stroke-width:2px, color:#fff;

    class H orange;
```
