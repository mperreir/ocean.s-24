<template>
  <div id="app">
    <header>
      <!-- Chat Header -->
      <h1>Green Data</h1>
    </header>
    
    <div class="chat-window">
        <!-- Chat messages -->
        <div class="chat-window">
          <div class="message right" v-for="message in messages" :key="message.id">
            <div v-if="message.type === 'text'">
              {{ message.content }}
            </div>
            <img v-else-if="message.type === 'image'" :src="message.content" alt="Sent Image" />
          </div>
        </div>
      </div>

    <div class="chat-input">
      <!-- Message Input -->
      <el-input v-model="input" style="width: 240px" placeholder="Please input" />

      <!-- Image and Video Upload -->
      <el-button type="primary" style="margin-left: 10px" @click="drawer = true">
        image
      </el-button>
      <el-button type="primary" style="margin-left: 10px" @click="drawer1 = true">
        video
      </el-button>

      <el-drawer
        v-model="drawer"
        title="choose an image"
        :direction="direction"
      >
        <div class="image-list">
          <img v-for="img in images" :src="img" :key="img" @click="sendMessage('image', img)" class="image-item" />
        </div>
      </el-drawer>

      <el-drawer
        v-model="drawer1"
        title="choose a video"
        :direction="direction"
      >
        
      </el-drawer>

      <!-- Send Button -->
      <el-button type="primary" style="margin-left: 10px" @click="sendMessage('text', input.value)">send</el-button>
    </div>
  </div>
</template>

<script setup>
import { ref } from 'vue'
import img from './/assets/logo.png'

const input = ref('')
const drawer = ref(false)
const drawer1 = ref(false)
const direction = ref('btt')
const images = ref([img])

const messages = ref([])

function sendMessage(type, content) {
  if (type === 'text' && input.value.trim()) {
    const newMessage = {
      id: Date.now(),
      type: type,
      content: input.value
    }
    messages.value.push(newMessage)
    input.value = ''
  } else if (type === 'image' && content) {
    const newMessage = {
      id: Date.now(),
      type: type,
      content: content
    }
    messages.value.push(newMessage)
    drawer.value = false 
  }
}


</script>

<style>
#app{
  display: flex;
  flex-direction: column;
}
header{
  display: flex;
  align-items: center; 
  justify-content: center; 
}
.chat-window {
  width: 90vw; 
  margin: auto;
  overflow-y: auto;
  height: 80vh;   
  border-radius: 10px;
  display: flex;
  flex-direction: column-reverse; 
  align-items: flex-end; 
}

.message {
  max-width: 60%;
  margin: 10px;
  padding: 10px;
  border-radius: 20px;
  background-color: #9ecffa; 
  word-wrap: break-word;
}

.user-message {
  align-self: flex-end; 
  background-color: #a0e7e5; 
}
.chat-input{
  margin-top: 2vh;
  display: flex;
  align-items: center; 
  justify-content: center; 
}
.image-list {
  display: flex;
  flex-wrap: wrap;
}
.image-item {
  width: 100px;
  height: 100px;
  margin: 10px;
  cursor: pointer;
}


</style>
