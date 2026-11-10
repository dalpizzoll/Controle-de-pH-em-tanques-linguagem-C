# ⚙️ Automação e Intertravamento de Segurança de pH (Linguagem C)

Sistema em C para telemetria de pH, cálculo de médias e intertravamento de segurança (*Safety Interlock*) em tanques industriais de processamento por batelada.

---

## 📌 Visão Geral

O projeto realiza o monitoramento e a avaliação de segurança para uma planta industrial configurável em $N$ tanques e $M$ sensores por tanque. 

Diferente de abordagens baseadas apenas em médias gerais, o algoritmo executa uma **triagem estrita por sensor individual**: se qualquer um dos sensores de um determinado tanque registrar valor fora da faixa de tolerância ($6.5 \le \text{pH} \le 7.5$), o atuador é imediatamente bloqueado para recirculação e um alarme crítico é contabilizado.

---

## 🛠️ Arquitetura e Recursos Técnicos

- **Alocação Dinâmica de Memória (`malloc`/`free`):** Matrizes de sensores e vetores de controle alocados dinamicamente em tempo de execução, com verificação de ponteiros nulos.
- **Estruturação Modular (`struct`):** Separação clara entre a planta física (`PlantaIndustrial`) e o sistema de controle (`SistemaControle`).
- **Lógica de Intertravamento (*Safety Interlock*):** Desativação imediata da válvula ao detectar a primeira inconformidade física em qualquer sensor do tanque.
- **Gestão Rigorosa de Memória:** Função dedicada para liberação total da heap após a conclusão do ciclo de operação.

---

## 📐 Estrutura de Dados

### Estruturas Principais
```c
typedef struct {
    float **sensores; // Matriz dinâmica [linhas x colunas]
    int linhas;       // Número de tanques
    int colunas;      // Número de sensores por tanque
} PlantaIndustrial;

typedef struct {
    float *vetor_medias;    // Armazena a média de pH de cada tanque
    int *vetor_atuadores; // Status do atuador (1 = Operando, 0 = Bloqueado)
    int total_alarmes;    // Contador global de alarmes críticos
} SistemaControle;
```

### Parâmetros Padrão do Sistema
- **Tanques (`linhas`):** `4`
- **Sensores por Tanque (`colunas`):** `3`
- **Faixa de Operação Segura:** `6.5` a `7.5`

---

## 🔄 Fluxo de Execução

1. `alocar_sistema()`: Reserva a memória RAM necessária e inicializa os atuadores como operacionais (`1`).
2. `inicializar_sensores()`: Captura os valores de pH informados via terminal.
3. `processar_dados()`: Calcula a média aritmética do pH de cada tanque.
4. `avaliar_seguranca()`: Avalia sensor a sensor. Caso $\text{pH} < 6.5$ ou $\text{pH} > 7.5$, altera o status do atuador para bloqueado (`0`) e incrementa o total de alarmes.
5. `emitir_relatorio()`: Exibe o relatório de operação no console.
6. `liberar_memoria()`: Desaloca toda a memória alocada dinamicamente.

---

## 🚀 Como Compilar e Executar

### Pré-requisitos
- Compilador C (`gcc`, `clang` ou `MSVC`).

### Compilação
```bash
gcc -Wall -Wextra -std=c11 main.c -o sistema_ph
```

### Execução
```bash
# Linux / macOS
./sistema_ph

# Windows
sistema_ph.exe
```

---

## 💻 Exemplo de Saída no Terminal

```text
Digite o pH (Tanque 1, Sensor 1): 7.0
Digite o pH (Tanque 1, Sensor 2): 7.1
Digite o pH (Tanque 1, Sensor 3): 6.9
Digite o pH (Tanque 2, Sensor 1): 6.2
Digite o pH (Tanque 2, Sensor 2): 7.0
Digite o pH (Tanque 2, Sensor 3): 7.1
...

--- RELATORIO DE OPERACAO ---
Tanque 1 -> Media: 7.00 | Status: Valvula Operando
Tanque 2 -> Media: 6.77 | Status: Bloqueada / Recirculacao
Tanque 3 -> Media: 7.05 | Status: Valvula Operando
Tanque 4 -> Media: 7.20 | Status: Valvula Operando
Total de Alarmes Criticos: 1
```
