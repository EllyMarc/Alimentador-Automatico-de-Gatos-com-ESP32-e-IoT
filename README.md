# Alimentador Automatico de Gatos com ESP32 e IoT

### Abstract
This paper presents the design of an automatic cat feeder using ESP32, featuring a servo motor-activated food dispensing mechanism. The prototype demonstrated reliable operation in maintaining its intended functionality and meeting its proposed objectives. Future improvements could focus on enhancing mechanical durability and energy efficiency. 

### Resumo
Este trabalho apresenta o projeto de um alimentador automático para gatos utilizando ESP32. Com um mecanismo que libera a ração acionado por servo motor. O protótipo demonstrou funcionamento confiável na manutenção e na proposta que ele visa oferecer. Melhorias futuras podem focar na durabilidade mecânica e eficiência energética. 

## 1. introdução
A tecnologia tem transformado a maneira como cuidamos dos nossos animais de estimação, oferecendo soluções práticas que facilitam o dia a dia e garantem o bem-estar dos pets. No caso dos gatos, animais com hábitos alimentares regulares e sensíveis a mudanças em sua rotina, a automação pode ser uma grande aliada para manter uma alimentação equilibrada e evitar problemas como obesidade ou desnutrição devido à alimentação irregular.


Pensando nisso, desenvolvemos um alimentador automático simples e eficiente, programado para distribuir porções de ração. A liberação de ração não segue um horário programado ou repetitivo, sendo definida de forma aleatória e imprevisível. Isso porque os gatos, embora sejam animais de rotina, podem desenvolver ansiedade quando a alimentação ocorre sempre no mesmo horário – como miados excessivos, agitação ou até comportamentos compulsivos.
    
    
> "[...] várias questões relacionadas ao comportamento alimentar são prejudicadas com esse tipo de comedouro [...] Comunicar-se com o animal durante a ausência pode gerar ainda mais ansiedade, pois o gato percebe o estímulo sem a presença do tutor." (AMMASSINO, Juliana.)
    
    
A aleatoriedade na distribuição da ração simula a dinâmica natural da caça, em que o alimento não está disponível em momentos previsíveis. Além do dispositivo em si, criamos um site totalmente autoral para acompanhar e ajustar o projeto. Apesar de suas funcionalidades ainda serem básicas, o desenvolvimento do site demandou esforço e aprendizado, mas, no final, conseguimos um resultado funcional que complementa nossa solução.


Com essa proposta, buscamos trazer praticidade para os donos de gatos e mais autonomia para os pets, contribuindo para uma rotina alimentar saudável e organizada.

### 1.1. Justificativa
Os gatos são animais de hábitos específicos, sensíveis a mudanças em sua rotina e altamente territorialistas. Quando suas necessidades naturais não são respeitadas, podem desenvolver problemas como obesidade, estresse, tédio e até doenças crônicas, como as renais, comuns em felinos domésticos. Tradicionalmente, os alimentadores automáticos disponíveis no mercado focam apenas na praticidade da dispensação de ração, sem considerar os aspectos comportamentais e fisiológicos dos gatos. Isso pode levar a uma alimentação inadequada, contribuindo para distúrbios de saúde e bem-estar.


Diante desse cenário, nosso projeto surge com a proposta de um alimentador inteligente que vai além da simples automação, integrando tecnologia e conhecimento sobre o comportamento felino para oferecer uma solução mais natural e adaptada às reais necessidades desses animais. Ao permitir que os gatos se alimentem em pequenas porções ao longo do dia, simulando seu instinto predatório, reduzimos os riscos de obesidade e problemas digestivos. Além disso, ao incorporar funcionalidades como controle remoto via aplicativo, dispensação interativa e monitoramento em tempo real, facilitamos a vida dos tutores, especialmente daqueles que, por compromissos profissionais ou viagens, não podem estar sempre presentes para supervisionar a alimentação de seus pets.

### 1.2. Objetivos
O projeto tem como objetivo desenvolver um alimentador automático inteligente que auxilie na rotina de alimentação de animais domésticos, oferecendo uma solução prática, tecnológica e eficiente. Nosso objetivo vai além de simplesmente oferecer um dispositivo que despeja comida: queremos proporcionar uma experiência inteligente, divertida e funcional, que respeita os hábitos do animal e traz mais comodidade para o tutor.
    

Assim nós buscamos resolver problemas como:

* Desperdício de ração


* Alimentação desregulada (excesso ou até mesmo a falta);

## 2. Materiais utilizados
Para o desenvolvimento do alimentador automático inteligente, foram selecionados componentes eletrônicos, módulos de comunicação e materiais estruturais que garantissem funcionalidade, precisão e durabilidade.

![Materiais Utilizados no Alimentador Automático](imagensREADME/materiaisUtilizados.png)

## 3. Montagem do circuito
O circuito conecta uma placa de controle ESP32 a um servo motor que libera a ração. Os pinos RX/TX permitem comunicação, enquanto D10-D13 controlam o servo via PWM. O servo tem três conexões básicas: alimentação (PWR), sinal (SB0) e terra (GB0).


 Quando acionado pela placa por horário programado, o servo abre o compartimento de ração. O circuito é simples e versátil, podendo ser melhor visualizado com ferramentas como Fritzing.


 A seguir, será apresentado o fluxograma que descreve o funcionamento lógico do alimentador automático. Este diagrama ilustra de maneira sistemática a sequência de operações executadas pelo sistema, desde a inicialização do dispositivo até a liberação controlada da ração, passando por todas as etapas de verificação e acionamento dos componentes.


O desenvolvimento do modelo 3D representou uma etapa crucial no projeto, permitindo a visualização em si e espacial completa do alimentador antes da prototipagem física, para melhor entender o que seria feito. Utilizando ferramenta de design tinkercad, foi possível criar uma representação fiel que integra todos os componentes eletrônicos e mecânicos em um formato ergonômico e funcional.

## 4. Resultados e Testes de Funcionamento

## 5. Dificuldades e soluções encontradas

## 6. Sugestões de Melhoria

## 7. Conclusão

## 8. Referências
