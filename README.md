# Lista 2

### Resposta Dissertativa Questão 3
- Ao utilizar a projeção do exercício anterior, o objeto desenhado fica muito pequeno e 3/4 fora da tela. No entanto, essa projeção é útil porque mapeia o espaço dos objetos para o espaço de tela, que vai de x=0 e y=0 até x=1920 e y=1080, por exemplo.

### Instruções

- Abrir o projeto pelo VSCode. Facilita se usar diretamente a opção de clonar repositório pela URL, dentro do VSCode.
- Clicar em "Build" na barra inferior e selecionar o compilador AMD64.
- É importante observar o diretório do arquivo "learnOpenGL.exe" após o build. Normalmente ele fica entro de build/debug, exigindo que adicionemos "../../" antes de acessar arquivos como os shaders, por exemplo. Se ele estiver um nível a mais ou a menos de profundidade, precisamos ajustar a quantidade de "../" no caminho dos arquivos.
- Os exercícios dessa lista estão anotados como comentário no arquivo main.cpp, de forma que, para executar um exercicio específico, basta "descomentar" as linhas comentadas desse exercício e comentar as referentes aos outros. Exemplo:
```
    // Tamanho padrao (utilizar para exercicios 4 e 5)
    glm::mat4 projection = glm::ortho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
//    // Exercicio 1
//    glm::mat4 projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,-1.0f,1.0f);
//    // Exercicios 2 e 3
//    glm::mat4 projection = glm::ortho(0.0f,800.0f,0.0f,600.0f,-1.0f,1.0f);
    shader.setMat4("projection", glm::value_ptr(projection));
```

- Dica: o atalho do VSCode para comentar/"descomentar" múltiplas linhas ao mesmo tempo é "CTRL + ;" (em teclado PT-BR, "CTRL + /" em teclado US). Peço desculpas pela inconveniência.
