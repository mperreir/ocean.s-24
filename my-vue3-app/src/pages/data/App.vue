<template>
  <div id="app">
    <div class="common-layout">
      <el-container>
        <el-aside>
          <div class="carousel-container">
            <div class="block text-center">
              <el-carousel height="150px">
                <el-carousel-item v-for="item in 4" :key="item">
                  <h3 class="small justify-center" text="2xl">{{ item }}</h3>
                </el-carousel-item>
              </el-carousel>
            </div>
          </div>
        </el-aside>
        <el-main>Main</el-main>
      </el-container>
    </div>
    <iframe style="width:100vw;height:100vh;border:0px;position:absolute;top:0;left:0;z-index:1;" src="https://cables.gl/view/6602dd7a4a0d23057b44297b"></iframe>
  </div>
</template>

<script setup>
// Script logic remains unchanged
</script>

<style scoped>
#app {
  width: 100vw;
  height: 100vh;
  position: relative; 
  overflow: hidden; 
}
.el-container{
  height: 100vh;
}
.el-aside{
  width: 40vw;
}
.demonstration {
  color: var(--el-text-color-secondary);
}
.carousel-container{
  position:absolute;
  z-index:2;
  height: inherit;
  width: inherit;
  display:flex;
  align-items:center;
  justify-content:center;
  background-color: red;
}
.el-carousel__item h3 {
  color: #475669;
  opacity: 0.75;
  line-height: 150px;
  margin: 0;
  text-align: center;
}
.el-carousel__item:nth-child(2n) {
  background-color: #99a9bf;
}
</style>
