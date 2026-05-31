# Atlas 

Um projeto simples em C para gerenciamento de usuários.

## Como rodar com Docker

### 1. Buildar a imagem
```bash
docker build -t atlas-app .
```

### 2. Rodar o container
```bash
docker run -it --rm atlas-app
```

---

## Como rodar localmente (Alternativo)

Se você tiver o `gcc` instalado:

```bash
gcc src/*.c -I include -o atlas && ./atlas 
```
