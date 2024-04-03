<template>
  <div id="app">
    <header>
      <!-- Chat Header -->
      <h1>Green Data</h1>
    </header>

    <div class="chat-window">
      <!-- Chat messages -->
      <div class="chat-window">
        <div id="init-message" class="message">Salut ! Envoie-moi des messages, photos ou vidéos pour voir le trajet de
          tes données en temps réel !</div>
        <div class="message right" v-for="message in messages" :key="message.id">
          <div v-if="message.type === 'text'">
            {{ message.content }}
          </div>
          <img v-else-if="message.type === 'image'" :src="message.content" alt="Sent Image" />
          <img v-else-if="message.type === 'video'" :src="message.content" alt="Sent Video" />
        </div>
      </div>
    </div>

    <div class="chat-input">
      <!-- Message Input -->
      <input id="inputmsg" v-model="input" placeholder="Écrivez un message…" />

      <div class="chat-input-buttons">
        <!-- Image and Video Upload -->
        <button id="image-button" style="chat-button" @click="drawer = true">
          <svg xmlns="http://www.w3.org/2000/svg" width="2em" height="em" viewBox="0 0 256 256">
            <path fill="currentColor"
              d="M224 160V48a16 16 0 0 0-16-16H48a16 16 0 0 0-16 16v160a16 16 0 0 0 16 16h160a16 16 0 0 0 16-16v-48ZM208 48v92.7L179.3 112a16.1 16.1 0 0 0-22.6 0L112 156.7L91.3 136a16.1 16.1 0 0 0-22.6 0L48 156.7V48Zm0 160H48v-28.7l32-32l20.7 20.7a16.1 16.1 0 0 0 22.6 0l44.7-44.7l40 40V208ZM91.5 100.5A11.9 11.9 0 0 1 88 92a12 12 0 0 1 24 0a12 12 0 0 1-12 12a12.3 12.3 0 0 1-8.5-3.5Z">
            </path>
          </svg>
        </button>
        <button id="video-button" style="chat-button" @click="drawer1 = true">
          <svg xmlns="http://www.w3.org/2000/svg" width="2em" height="2em" viewBox="0 0 256 256">
            <path fill="currentColor"
              d="M244 73.1a7.7 7.7 0 0 0-8 0l-44 25.1V92a40 40 0 0 0-40-40H24A16 16 0 0 0 8 68v96a40 40 0 0 0 40 40h128a16 16 0 0 0 16-16v-30.2l44 25.1a8.3 8.3 0 0 0 4 1.1a8 8 0 0 0 4-1.1a7.8 7.8 0 0 0 4-6.9V80a7.8 7.8 0 0 0-4-6.9ZM176 188H48a24.1 24.1 0 0 1-24-24V68h128a24.1 24.1 0 0 1 24 24v96Zm56-25.8l-40-22.8v-22.8l40-22.8Z" />
          </svg>
        </button>

        <el-drawer v-model="drawer" title="Envoyer une image" :direction="direction" size="50%">
          <div class="image-list">
            <img v-for="img in images" :src="img" :key="img" @click="sendMessage('image', img)" class="image-item" />
          </div>
        </el-drawer>

        <el-drawer v-model="drawer1" title="Envoyer une vidéo" :direction="direction" size="50%">
          <div class="image-list">
            <img v-for="v in videos" :src="v" :key="v" @click="sendMessage('video', v)" class="image-item" />
          </div>
        </el-drawer>

        <!-- Send Button -->
        <button class="chat-send" @click="sendMessage('text', input.value)"> Envoyer </button>
      </div>
    </div>
  </div>
</template>

<script setup>
import { io } from 'socket.io-client'
const socket = io(['http://localhost:3010','http://192.168.1.153:3010/',"http://192.168.1.153"]);
import { ref } from 'vue';
import im1 from './/assets/images/i1.png'
import im2 from './/assets/images/i2.png'
import im3 from './/assets/images/i3.png'
import v1 from './/assets/videos/v1.png'
import v2 from './/assets/videos/v2.png'
import v3 from './/assets/videos/v3.png'
import v4 from './/assets/videos/v4.png'

const input = ref('')
const drawer = ref(false)
const drawer1 = ref(false)
const direction = ref('btt')
const images = ref([im1, im2, im3])
const videos = ref([v1, v2, v3, v4])

const messages = ref([]);
const fakeUserIP = `${getRandomArbitrary(1, 255)}.${getRandomArbitrary(1, 255)}.${getRandomArbitrary(1, 255)}.${getRandomArbitrary(1, 255)}`;

document.addEventListener("DOMContentLoaded", () => {
  const inputField = document.querySelector("#inputmsg");
  const chatWindow = document.querySelector(".chat-window");
  const sendButton = document.querySelector(".chat-send");
  const imageButton = document.querySelector("#image-button");
  const videoButton = document.querySelector("#video-button");

  inputField.addEventListener("focus", () => {
    sendButton.style.display = "block";
    imageButton.style.display = "none";
    videoButton.style.display = "none";
  });

  chatWindow.addEventListener("DOMNodeInserted", (e) => {
    if (e.target.parentNode.className == chatWindow.className) {
      sendButton.style.display = "none";
      imageButton.style.display = "flex";
      videoButton.style.display = "flex";
      window.scrollTo(0, document.body.scrollHeight);
    }
  });
});

function getRandomArbitrary(min, max) {
  return String(Math.floor(Math.random() * (max - min) + min));
}

function sendMessage(type, content) {
  const address = fakeUserIP;
  if (type === 'text' && input.value.trim()) {
    const newMessage = {
      id: Date.now(),
      type: type,
      content: input.value,
      address: address
    }
    messages.value.push(newMessage)
    socket.emit('send message', newMessage);
    input.value = ''
  } else if (type === 'image' && content) {
    const newMessage = {
      id: Date.now(),
      type: type,
      content: content,
      address: address
    }
    messages.value.push(newMessage)
    socket.emit('send message', newMessage);
    drawer.value = false
  } else if (type === 'video' && content) {
    const newMessage = {
      id: Date.now(),
      type: type,
      content: content,
      address: address
    }
    messages.value.push(newMessage)
    socket.emit('send message', newMessage);
    drawer1.value = false
  }

}

</script>


<style>
@font-face {
  font-family: Outfit;
  src: url('./assets/fonts/Outfit-VariableFont_wght.ttf');
}

html,
body {
  margin: 0px;
  padding: 0px;
  font-family: Outfit, sans-serif;
}

#app {
  display: flex;
  flex-direction: column;
  
}

h1 {
  position: fixed;
  background-color: #fff;
  width: 100%;
  top: 0px;
  display: flex;
  align-items: center;
  justify-content: center;
  padding: 4vh 2vh;
  margin: 0px;
  background-color: rgba(255, 255, 255, .9);
  backdrop-filter: blur(4px);
  font-size: 1.25rem;
}

.chat-window {
  width: 90vw;
  padding-bottom: 4px;
  margin: 6vh auto;
  overflow-y: auto;
  border-radius: 10px;
  display: flex;
  flex-direction: column;
  align-items: flex-end;
}

.message {
  max-width: 60%;
  margin: 4px;
  padding: 12px 16px;
  border-radius: 24px 24px 2px 24px;
  background-color: #ebeaea;
  word-wrap: break-word;
  font-size: 1rem;
  font-weight: 300;
}

#init-message {
  border-radius: 24px 24px 24px 2px;
  background-color: #9747ff;
  color: white;
  align-self: flex-start;
}

.chat-input {
  padding: 2vh 2vh 4vh 2vh;
  display: flex;
  gap: 16px;
  align-items: center;
  justify-content: center;
  position: fixed;
  bottom: 0px;
  width: calc(100% - 2vh - 16px);
  background-color: #fff;
}

.chat-input-buttons {
  display: flex;
}

.chat-button {
  display: block;
}

.chat-send {
  display: none;
  width: fit-content;
  font-family: "Outfit";
  font-weight: 700;
  color: #4600a2;
}

button {
  background-color: transparent;
  border: none;
  height: 48px;
  width: 48px;
  display: flex;
  align-items: center;
  justify-content: center;
  opacity: .75;
}

.image-list {
  display: flex;
  height: fit-content;
  overflow-x: scroll;
}

.image-item {
  height: 200px;
  margin: 16px;
  cursor: pointer;
}

input {
  border-radius: 100px;
  padding: 16px 18px;
  border: none;
  background-color: #ebeaea;
  color: #000000;
  width: 100%;
  font-family: Outfit;
  font-size: 1rem;
}

img {
  border-radius: 16px;
}
</style>
