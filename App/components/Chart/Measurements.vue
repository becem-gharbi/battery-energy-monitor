<template>
    <ChartBase :options="options" />
</template>

<script setup lang="ts">

const props = defineProps<{ measurements?: Measurements }>()

const options = computed<HighchartsOptions>(() => ({
    plotOptions: {
        series: {
            lineWidth: 3
        }
    },
    chart: {
        zooming: {
            type: "x"
        },
    },
    title: {
        text: ""
    },
    xAxis: {
        type: 'datetime',
        dateTimeLabelFormats: {
            millisecond: '%H:%M:%S',
            second: '%H:%M:%S',
            minute: '%H:%M',
            hour: '%H:%M',
            day: '%e. %b',
            week: '%e. %b',
            month: '%b \'%y',
            year: '%Y'
        },

    },
    yAxis: {
        title: {
            text: ""
        }
    },
    series: [{
        name: "Current",
        type: 'line',
        data: props.measurements?.current
    }, {
        name: "Voltage",
        type: 'line',
        data: props.measurements?.voltage
    }, {
        name: "Power",
        type: 'line',
        data: props.measurements?.power
    }],
}))
</script>