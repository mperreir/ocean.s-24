<template>
  <div id="app">
    <div class="common-layout">
      <el-container>
      <el-header><h2> Green data </h2></el-header>
        <el-container>
          <el-aside>
              <div class="block text-center">
                <el-carousel height="50vh">
                  <el-carousel-item v-for="item in 4" :key="item">
                    <h3 class="small justify-center" text="2xl">{{ item }}</h3>
                  </el-carousel-item>
                </el-carousel>
              </div>
          </el-aside>
          <el-main>
            
            <img src="./assets/maqutte.png" class="maqutte"/>
          </el-main>
        </el-container>
      </el-container>
    </div>
    <el-table :data="tableData" style="width: 40vw; height: 30vh; border-radius: 10px; z-index: 2; position: absolute; top: 65vh; left: 15vw;">
      <el-table-column prop="address" label="Address" />
      <el-table-column prop="action" label="Action" />
    </el-table>
    <iframe style="width:100vw;height:100vh;border:0px;position:absolute;top:0;left:0;z-index:1;" src="https://cables.gl/view/6602dd7a4a0d23057b44297b"></iframe>
  </div>
</template>

<script setup>
import{io} from 'socket.io-client'
import { ref, onMounted} from 'vue';
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
const tableData = ref([]);
onMounted(() => {

  socket.on('new message', (newMessage) => {
    if(newMessage.type === 'video'){
        tableData.value.push({
        address: newMessage.address,
        action: `a envoyé un ${newMessage.type} (${newMessage.content.length*100} bytes)` 
      });
    }
    else{
        tableData.value.push({
        address: newMessage.address,
        action: `a envoyé un ${newMessage.type} (${newMessage.content.length} bytes)` 
      });
    }
    
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

.el-header{
  z-index: 2;
  height: 10vh;
  width: 100vw;
  display: flex;
  align-items: center; 
  justify-content: center;
}

.el-container{
  margin-left: 2vw;
  height: 90vh;
}

.el-aside{
  width: 40vw;
  height: 100vh;
  z-index: 2;
  mix-blend-mode: screen;
}

.demonstration {
  color: var(--el-text-color-secondary);
}

.el-carousel__item h3 {
  color: #475669;
  opacity: 0.75;
  line-height: 150px;
  margin: 0;
  text-align: center;
}

.el-carousel__item{
  border-radius: 10px;
}

.el-carousel__item:first-child{
  background: url(./assets/test.png)
}

.el-carousel__item:nth-child(2n) {
  background-color: #99a9bf;
}

.el-carousel__item:nth-child(2n + 1) {
  background-color: #d3dce6;
}


.el-main{
  z-index: 2;
  position: absolute;
  bottom: 0px;
  mix-blend-mode: screen;
  display: flex;
  flex-direction: column;
  align-items: center; 
  justify-content: center;
  height: inherit;
  overflow: hidden;
}

h2 {
  margin-left: 40vw;
  color: #CFF0FD;
  font-size: 50px;
  height: 50px;
  font-family: 'Akira Expanded';
  font-style: normal;
  font-weight: 800;
  line-height: 200%;
}

.maqutte{
  width: 40vw;
  height: inherit;
}

.el-table{
  width: 40vw; 
  height: 30vh; 
  border-radius: 10px; 
  z-index: 2; 
  position: absolute; 
  top: 65vh; 
  left: 15vw;
  background-color: #0A1119;
  --el-table-tr-bg-color: #0A1119;
  --el-table-header-bg-color:  #0A1119;
  --el-table-border: 0px;
  --el-table-text-color: #CFF0FD;
  --el-table-header-text-color: #CFF0FD;
  --el-table-row-hover-bg-color: #0A1119;
  mix-blend-mode: screen;
}
</style>
