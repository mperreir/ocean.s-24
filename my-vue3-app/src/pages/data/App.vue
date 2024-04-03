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
              <p class="text">de la facture d’un datacenter correspond aux <strong>dépenses énergétiques</strong> liées
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
            <div v-for="log in data" :key="log.id" class="logs-text">
              <div>
                <p>{{ log.address }} a envoyé {{ log.article }} <strong>{{ log.type }}</strong> ({{ log.size }})</p>
              </div>
            </div>
          </div>
        </section>
      </section>
      <main>
        <h2>Green Data</h2>
        <section class="images">
          <img class="maqutte" src="./assets/maqutte.gif" alt="">
        </section>
      </main>
    </div>
    <iframe style="width:100vw; height:100vh; border:0px; position:absolute; top:0; left:0; z-index:1;"
    src="https://cables.gl/view/6602dd7a4a0d23057b44297b"></iframe>
  </div>
</template>

<script setup>
import { io } from 'socket.io-client'
import { ref, onMounted } from 'vue';

import s1 from './/assets/notificationsounds/android.mp3'
import s2 from './/assets/notificationsounds/discord.mp3'
import s3 from './/assets/notificationsounds/iphone.mp3'
import s4 from './/assets/notificationsounds/iphone1.mp3'
import s5 from './/assets/notificationsounds/iphone2.mp3'
import s6 from './/assets/notificationsounds/messenger.mp3'
import s7 from './/assets/notificationsounds/samsung.mp3'
import s8 from './/assets/notificationsounds/snapchat.mp3'

const socket = io('http://localhost:3010');

const sound1 = new Audio(s1);
const sound2 = new Audio(s2);
const sound3 = new Audio(s3);
const sound4 = new Audio(s4);
const sound5 = new Audio(s5);
const sound6 = new Audio(s6);
const sound7 = new Audio(s7);
const sound8 = new Audio(s8);
const sounds = [sound1, sound2, sound3, sound4, sound5, sound6, sound7, sound8];

document.addEventListener("DOMContentLoaded", function () {
  setInterval(changeSlide, 10000);
})

let currentSlideNumber = 0;
function changeSlide() {
  currentSlideNumber++;
  let currentSlide = ".slide" + currentSlideNumber;
  document.querySelector(currentSlide).style.display = "none";

  if (currentSlideNumber > 3) {
    document.querySelectorAll(".slide").forEach(slide => slide.style.display = "block");
    currentSlideNumber = 0;
  }
}

function playSound() {
  let r = Math.floor(Math.random() * sounds.length);
  sounds[r].play();
}

const data = ref([]);
onMounted(() => {

  socket.on('new message', (newMessage) => {
    if (newMessage.type === 'video') {
      data.value.push({
        id: newMessage.id,
        address: newMessage.address,
        article: "une",
        type: "vidéo",
        size: "45 Mo"
      });
    }
    else if (newMessage.type === 'image') {
      data.value.push({
        id: newMessage.id,
        address: newMessage.address,
        article: "une",
        type: "image",
        size: "1.3 Mo"
      });
    }
    else if (newMessage.type === 'text') {
      data.value.push({
        id: newMessage.id,
        address: newMessage.address,
        article: "un",
        type: "message",
        size: String(newMessage.content.length) + " o"
      });
    }
    playSound();
  });
});
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
  min-height: 45vh;
  border-radius: 16px;
  border: solid #CFF0FD 2px;
  background-color: #0a111979;
  backdrop-filter: blur(48px);
  top: 15vh;
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
  bottom: 12vh;
  left: 29vw;
  height: 30vh;
  width: 22vw;
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
  line-height: 150%;
  word-wrap: break-word;
}

main {
  display: flex;
  flex-direction: column;
  justify-content: space-between;
  width: 50%;
  height: 100%;
}

.images {
  display: flex;
  align-items: stretch;
  justify-content: center;
}

.maqutte {
  width: 80%;
  height: 70%;
  object-fit: contain;
}
</style>
