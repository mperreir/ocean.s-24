<template>
  <div id="app">
    <div class="container">
      <section class="windows">
        <section class="slides">
          <div class="window-head">
            <h3>data_info</h3>
          </div>
          <div class="slides-container">
            <div class="slide slide1">
              <h4>ENERGIE</h4>
              <p class="text">En moyenne, un datacenter de 10000m² consomme <strong>autant d’énergie</strong> qu’une
                ville de</p>
              <p class="big-text">50 000</p>
              <p class="small-text">habitants, sur une année.</p>
            </div>
            <div class="slide slide2">
              <h4>ENERGIE</h4>
              <p class="big-text">50%</p>
              <p class="text">de la facture d’un datacenter correspond aux <strong> dépenses énergétiques</strong> liées
                au refroidissement des serveurs.</p>
            </div>
            <div class="slide slide3">
              <p class="big-text">MESSAGE</p>
              <p class="small-text">1 octet par caractère. Message court : ~100 o.</p>
              <p class="big-text">IMAGE HD</p>
              <p class="small-text">10 000x plus qu’un message. ~1 Mo.</p>
              <p class="big-text">VIDEO HD</p>
              <p class="small-text">1 à 2 Mo/seconde. 30s compressées : ~45 Mo.</p>
            </div>
            <div class="slide slide4">
              <h4>EMPREINTE</h4>
              <p class="big-text">25%</p>
              <p class="text">des émissions mondiales de gaz à effet de serre liées au numérique, sont émises par les
                datacenters.</p>
            </div>
          </div>
        </section>
        <section class="logs">
          <div class="window-head">
            <h3>user_log</h3>
          </div>
          <div class="logs-content">
            <div class="logs-text">
              {{ data.content }}
            </div>
          </div>
        </section>
      </section>
      <main>
        <h2>Green Data</h2>
        <section class="images">
          <img class="maqutte" src="./assets/maqutte.png" alt="">
        </section>
      </main>
    </div>
    <iframe style="width:100vw;height:100vh;border:0px;position:absolute;top:0;left:0;z-index:1;"
      src="https://cables.gl/view/6602dd7a4a0d23057b44297b"></iframe>
  </div>
</template>

<script setup>
import { io } from 'socket.io-client'
import { ref, onMounted } from 'vue';
const socket = io('http://localhost:3000')

// const tableData = [
//   {
//     address: '123.45.67.890',
//     action: 'a envoyé un message (28 o)'
//   },
//   {
//     address: '123.45.67.890',
//     action: 'a envoyé un image (28 kb)'
//   },
//   {
//     address: '123.45.67.890',
//     action: 'a envoyé un video (28 mb)'
//   },
// ]

document.addEventListener("DOMContentLoaded", function () {
  setInterval(changeSlide, 10000);
})

let currentSlideNumber = 0;
function changeSlide() {
  currentSlideNumber++;
  let currentSlide = ".slide" + currentSlideNumber;
  document.querySelector(currentSlide).style.display = "none";

  if (currentSlideNumber > 3) {
    document.querySelector(".slide1").style.display = "block";
    document.querySelector(".slide2").style.display = "block";
    document.querySelector(".slide3").style.display = "block";
    document.querySelector(".slide4").style.display = "block";
    currentSlideNumber = 0;
  }

}

const tableData = ref([]);
onMounted(() => {

  socket.on('new message', (newMessage) => {
    if (newMessage.type === 'video') {
      tableData.value.push({
        address: newMessage.address,
        action: `a envoyé un ${newMessage.type} (${newMessage.content.length * 100} octets)`
      });
    }
    else {
      tableData.value.push({
        address: newMessage.address,
        action: `a envoyé un ${newMessage.type} (${newMessage.content.length} octets)`
      });
    }

  });
});
</script>
<script>
const data = ref([]);

document.addEventListener("click", function () {
  data.value.push({
    address: "newMessage.address",
    action: "a envoyé un newMessage.type"
  });
  console.log(data);
})
</script>

<style>
@font-face {
  font-family: Akira Expanded;
  src: url('./assets/fonts/AkiraExpandedDemo.otf');
}

@font-face {
  font-family: JetBrains Mono;
  src: url('./assets/fonts/JetBrainsMono-VariableFont_wght.ttf');
}

body {
  margin: 0px;
  font-family: JetBrains Mono;
}

#app {
  width: 100vw;
  height: 100vh;
  position: relative;
  overflow: hidden;
}

h2 {
  color: #CFF0FD;
  width: 100%;
  display: flex;
  justify-content: center;
  font-size: 3rem;
  font-family: 'Akira Expanded';
  font-style: normal;
  font-weight: 800;
  line-height: 200%;
  margin-bottom: 16px;
}

h3 {
  color: #CFF0FD;
  font-size: 1.1rem;
  font-weight: 400;
  margin: 8px 0px 8px 20px;
}

.logs h3 {
  padding-top: 4px;
  font-size: 1rem;
}

.container {
  position: relative;
  z-index: 2;
  height: 100%;
  width: 100%;
  display: flex;
}

.windows {
  position: relative;
  z-index: 3;
  width: 50%;
  height: 100%;
  display: block;
}

.window-head {
  border-bottom: solid #CFF0FD 2px;
}

.logs .window-head {
  border-bottom: solid #cff0fd7f 1px;
}

.slides {
  position: relative;
  width: 42vw;
  border-radius: 16px;
  border: solid #CFF0FD 2px;
  background-color: #0a111979;
  backdrop-filter: blur(48px);
  top: 10vh;
  left: 5vw;
  overflow: hidden;
}

.slides-container {
  display: flex;
  width: max-content;
  overflow: hidden;
}

.slide {
  width: calc(42vw - 64px);
  padding: 0px 32px 32px 32px;
}

.text {
  margin: 16px 0px 0px 0px;
  font-size: 1.25rem;
  color: #CFF0FD;
  width: 85%;
  line-height: 150%;
}

.big-text {
  margin: 0px;
  font-family: Akira Expanded;
  font-size: 5rem;
  background: linear-gradient(#CFF0FD, #97CECC);
  background-clip: text;
  -webkit-text-fill-color: transparent;
}

.small-text {
  font-size: 1rem;
  color: #CFF0FD;
  margin: 0px;
}

.slide2 .big-text {
  margin-top: 16px;
}

.slide2 .text {
  width: 90%;
}

.slide3 .big-text {
  font-size: 2.5rem;
  margin-top: 24px;
}

.slide4 .big-text {
  margin-top: 16px;
}

h4 {
  font-family: Akira Expanded;
  font-size: 2.5rem;
  color: #CFF0FD;
  margin: 16px 0px 0px 0px;
}

.logs {
  position: absolute;
  bottom: 10vh;
  left: 28vw;
  height: 30vh;
  width: 26vw;
  background-color: #0a1119c7;
  border-radius: 16px;
  color: #CFF0FD;
  backdrop-filter: blur(10px);
}

.logs-content {
  display: flex;
  height: calc(100% - 3.5rem);
  flex-direction: column;
  justify-content: end;
  overflow: hidden;
}

.logs-text {
  display: flex;
  flex-direction: column-reverse;
  gap: 4px;
}

.logs-content p {
  margin: 0px 16px;
  font-size: .75rem;
  font-weight: 200;
  word-wrap: break-word;
}

main {
  display: flex;
  flex-direction: column;
  width: 50%;
  height: 100%;
}

.images {
  display: flex;
  align-items: center;
  justify-content: center;
}

.maqutte {
  width: 70%;
}
</style>
