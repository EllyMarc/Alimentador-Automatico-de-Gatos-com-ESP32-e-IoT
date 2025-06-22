let contador = 0;
const limite = 10;
let emProcesso = false;
let timerId = null;

// Envia comando pro ESP32
function enviarComando(comando) {
  return fetch(comando).catch(error => console.error('Erro:', error));
}

// Atualiza barra de progresso e contador visual
function atualizarUI() {
  document.getElementById('contador-texto').innerText = `${contador}/${limite}`;
  const porcentagem = (contador / limite) * 100;
  document.getElementById('barra-progresso').style.width = `${porcentagem}%`;
}

// Atualiza o status do servo no painel
function setStatusServo(estado) {
  const statusDiv = document.getElementById('status-servo');

  if (estado === 'funcionando') {
    statusDiv.innerText = 'Funcionando';
    statusDiv.className = 'status-indicador funcionando';
  } else if (estado === 'alimentado') {
    statusDiv.innerText = 'Alimentado';
    statusDiv.className = 'status-indicador alimentado';
    setTimeout(() => {
      setStatusServo('repouso');
    }, 4000);
  } else {
    statusDiv.innerText = 'Em Repouso';
    statusDiv.className = 'status-indicador repouso';
  }
}

// Finaliza contagem se atingido limite
function encerrarContagem() {
  document.getElementById('status-clique').innerText = 'Limite atingido!';
  const botao = document.getElementById('botao-clique');
  botao.disabled = true;
  botao.style.opacity = '0.5';
  if (timerId) clearTimeout(timerId);
}

// Ação centralizada de alimentação (botão ou tempo)
async function acionarAlimentacao() {
  if (contador >= limite || emProcesso) return;

  emProcesso = true;
  contador++;
  atualizarUI();

  await enviarComando('/servo');

  document.getElementById('status-clique').innerText = 'Clique registrado!';
  document.getElementById('status-led').innerText = 'Ligado';
  setStatusServo('funcionando');

  setTimeout(() => {
    document.getElementById('status-led').innerText = 'Desligado';
    document.getElementById('status-clique').innerText = 'Clique!';
    setStatusServo('alimentado');
    emProcesso = false;

    if (contador >= limite) {
      encerrarContagem();
    } else {
      iniciarTemporizador(); // reinicia tempo
    }
  }, 2000);
}

// Botão clicado
function handleBotaoClique() {
  acionarAlimentacao();
}

// Tempo esgotado → simula clique
function handleTempoAcabou() {
  acionarAlimentacao();
}

// Converte segundos para HH:MM:SS
function segundosParaTempo(segundos) {
  const h = Math.floor(segundos / 3600);
  const m = Math.floor((segundos % 3600) / 60);
  const s = segundos % 60;
  return `${String(h).padStart(2, '0')}:${String(m).padStart(2, '0')}:${String(s).padStart(2, '0')}`;
}

// Atualiza o tempo restante na interface
function atualizarContadorTempo() {
  fetch('/tempo')
    .then(res => res.text())
    .then(segundos => {
      const tempoFormatado = segundosParaTempo(parseInt(segundos));
      document.getElementById('contador-tempo').innerText = tempoFormatado;
    })
    .catch(console.error);
}

// Inicia o temporizador para acionar servo se o tempo acabar
function iniciarTemporizador() {
  if (contador >= limite) return;
  if (timerId) clearTimeout(timerId);

  fetch('/tempo')
    .then(res => res.text())
    .then(segundos => {
      const tempoMs = parseInt(segundos) * 1000;

      if (tempoMs <= 0 || isNaN(tempoMs)) return;

      timerId = setTimeout(() => {
        if (!emProcesso && contador < limite) {
          handleTempoAcabou();
        }
      }, tempoMs);
    })
    .catch(console.error);
}

//Quando a página web carregar completamente, essas funções serão executadas
window.onload = () => {
  atualizarContadorTempo();
  setInterval(atualizarContadorTempo, 1000);
  setStatusServo('repouso');
  iniciarTemporizador();
  atualizarUI();
};

