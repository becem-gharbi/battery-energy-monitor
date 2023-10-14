<template>
    <div :style="{ width: `${width}px`, height: `${height}px` }">
        <ClientOnly>
            <Chart :options="highchartsOptions"></Chart>
        </ClientOnly>
    </div>
</template>

<script setup lang="ts">
import { Chart } from 'highcharts-vue'
import { defu } from 'defu'

const props = defineProps<{
    options: HighchartsOptions,
    height?: number,
    width?: number
}>()

const naiveTheme = useThemeVars()

const highchartsOptions = computed<HighchartsOptions>(() => defu(
    props.options,
    {
        chart: {
            height: props.height,
            width: props.width,
            backgroundColor: naiveTheme.value.bodyColor,
            plotBackgroundColor: naiveTheme.value.bodyColor,
            style: {
                fontFamily: naiveTheme.value.fontFamily,
            },
        },

        accessibility: {
            enabled: false
        },

        title: {
            style: {
                color: naiveTheme.value.textColor1
            }
        },

        xAxis: {
            lineColor: "#EDEDED82",
            title: {
                style: {
                    color: naiveTheme.value.textColor2,
                }
            },
            labels: {
                style: {
                    color: naiveTheme.value.textColor2,
                }
            },
        },

        yAxis: {
            gridLineColor: "#DBDBDB51",
            title: {
                style: {
                    color: naiveTheme.value.textColor2,
                }
            },
            labels: {
                style: {
                    color: naiveTheme.value.textColor2,
                }
            },
        },

        legend: {
            itemStyle: {
                color: naiveTheme.value.textColor2
            }
        },

        credits: {
            enabled: false,
        }
    } as HighchartsOptions
))

</script>
