<template>
	<view class="content">
		<image class="logo" src="/static/logo.png"></image>
	
			
			
			
			 <view>13232</view>
			 <view id="box"></view>

			
			
	</view>

</template>



<script>
	import * as echarts from 'echarts' 
	import axios from "axios"
	
	
	export default {
		data() {
			return {
				title: 'Hello',
				t_data:[],
				
			}
		},
		mounted() {
			setInterval(this.initChart,1000)
	 
		},
		
		
methods: {
	
	
  async initChart() {
	 var myChart = echarts.init(document.getElementById("box"));
	 var t_array = new Array()
	 var time_array = new Array()
	 
	 myChart.resize({  
	     width: 300,   // 新的宽度  
	     height: 300   // 新的高度  
	 });
	 
	 
	 
	 var data = await axios.get("http://154.12.26.163:5000/gett")
	 
	 var data = data.data
	 
	 console.log(data)
	 
	 var t_array = new Array()
	 
	 for(var i=0;i<6;i++){
		 t_array.push(data[i][0])
		 time_array.push(data[i][1])
	 }
	 
	 console.log(t_array)
	 console.log(time_array)
	 
	 
	 
	 


	 
	 
	

  // 指定配置项和数据
    var option = {
        title: {
            text: '实时温度',
        },
        tooltip: {},
        tooltip: {
            trigger: 'axis'
        },
        legend: {
            data: ['温度'],
        },
        xAxis: {
            data: time_array, //x坐标系
        },
        yAxis: {
            min:"dataMin",
            max:"dataMax"
        },
        series: [  //数据
            {
                name: '温度',
                type: 'line',
                data: t_array,
                smooth: true
            },
        ],
    };
	
    myChart.setOption(option) // 将配置应用到图表实例
  },
  
  test(){
	  alert(123)
  }
}

	}
</script>

<style>
	.content {
		display: flex;
		flex-direction: column;
		align-items: center;
		justify-content: center;
	}

	.logo {
		height: 200rpx;
		width: 200rpx;
		margin-top: 200rpx;
		margin-left: auto;
		margin-right: auto;
		margin-bottom: 50rpx;
	}

	.text-area {
		display: flex;
		justify-content: center;
	}

	.title {
		font-size: 36rpx;
		color: #8f8f94;
	}
</style>
