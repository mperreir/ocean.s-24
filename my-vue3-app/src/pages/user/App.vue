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
import { ref, onMounted } from 'vue';

// Importing images and videos for use in the app
import im1 from './assets/images/i1.png';
import im2 from './assets/images/i2.png';
import im3 from './assets/images/i3.png';
import v1 from './assets/videos/v1.png';
import v2 from './assets/videos/v2.png';
import v3 from './assets/videos/v3.png';
import v4 from './assets/videos/v4.png';

const input = ref('');
const messages = ref([]);
const drawer = ref(false);
const drawer1 = ref(false);
const direction = ref('btt');
const images = ref([im1, im2, im3]);
const videos = ref([v1, v2, v3, v4]);

// Simulated user IP for demonstration purposes
const fakeUserIP = `${getRandomArbitrary(1, 255)}.${getRandomArbitrary(1, 255)}.${getRandomArbitrary(1, 255)}.${getRandomArbitrary(1, 255)}`;

// Utility function to generate random numbers
function getRandomArbitrary(min, max) {
  return String(Math.floor(Math.random() * (max - min) + min));
}

// Function to send messages using HTTP POST
async function sendMessage(type, content) {
  const message = {
    id: Date.now(),
    type,
    content: type === 'text' ? input.value : content,
    address: fakeUserIP,
  };

  try {
    const response = await fetch(['http://localhost:3010/ocean-2/messages',"http://hyblab.polytech.univ-nantes.fr/ocean-2/messages"], {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(message),
    });
    if (!response.ok) throw new Error('Network response was not ok.');

    messages.value.push(message); // Optionally, update local messages list
    if (type === 'text') input.value = ''; // Clear text input
    if (type === 'image') drawer.value = false; // Close image drawer
    if (type === 'video') drawer1.value = false; // Close video drawer
  } catch (error) {
    console.error('Error sending message:', error);
  }
}

// Function to periodically fetch messages
async function fetchMessages() {
  try {
    const response = await fetch(['http://localhost:3010/ocean-2/messages',"http://hyblab.polytech.univ-nantes.fr/ocean-2/messages"]);
    if (!response.ok) throw new Error('Network response was not ok.');
    const data = await response.json();
    messages.value = data; // Update local messages with server data
  } catch (error) {
    console.error('Error fetching messages:', error);
  }
}

// Fetch messages on component mount and set interval for periodic fetching
onMounted(() => {
  fetchMessages();
  setInterval(fetchMessages, 1000); // Adjust interval as needed
});

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
