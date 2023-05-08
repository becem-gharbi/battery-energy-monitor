<template>
    <n-form ref="formRef" :model="model" :rules="rules" @submit="onSubmit">
        <n-form-item label="Debug" path="debug">
            <n-select v-model:value="model.debug" :options="[{ label: 'Yes', value: 1 }, { label: 'No', value: 0 }]" />
        </n-form-item>

        <n-form-item label="Sample Rate" path="sampleRate">
            <n-input-number v-model:value="model.sampleRate" />
        </n-form-item>

        <n-form-item label="Saving Rate" path="savingRate">
            <n-input-number v-model:value="model.savingRate" />
        </n-form-item>

        <n-form-item label="Current Gain" path="currentGain">
            <n-input-number v-model:value="model.currentGain" />
        </n-form-item>

        <n-form-item label="Current Offset" path="currentOffset">
            <n-input-number v-model:value="model.currentOffset" />
        </n-form-item>

        <n-form-item label="Voltage Gain" path="voltageGain">
            <n-input-number v-model:value="model.voltageGain" />
        </n-form-item>

        <n-form-item label="Voltage Offset" path="voltageOffset">
            <n-input-number v-model:value="model.voltageOffset" />
        </n-form-item>

        <n-form-item>
            <n-button attr-type="submit" type="primary">
                Save
            </n-button>
        </n-form-item>
    </n-form>
</template>

<script setup lang="ts">
import type { FormInst } from "naive-ui"

const props = defineProps<{ settings: Settings }>()

const formRef = ref<FormInst>()

const model = ref<Settings>(props.settings)

const rules = ref()

function onSubmit() {
    formRef.value?.validate((errors) => {
        if (!errors) {
            useState("settings").value = model
        }
    })
}
</script>