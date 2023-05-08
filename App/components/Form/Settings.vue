<template>
    <n-form ref="formRef" :model="model" :rules="rules" @submit.prevent="onSubmit">
        <n-form-item label="Debug" path="debug">
            <n-select v-model:value="model.debug" :options="[{ label: 'Yes', value: 1 }, { label: 'No', value: 0 }]" />
        </n-form-item>

        <n-form-item label="Sample Rate" path="sampleRate">
            <n-input-number v-model:value="model.sampleRate" class="w-full" />
        </n-form-item>

        <n-form-item label="Saving Rate" path="savingRate">
            <n-input-number v-model:value="model.savingRate" class="w-full"/>
        </n-form-item>

        <n-form-item label="Current Gain" path="currentGain">
            <n-input-number v-model:value="model.currentGain" class="w-full"/>
        </n-form-item>

        <n-form-item label="Current Offset" path="currentOffset">
            <n-input-number v-model:value="model.currentOffset" class="w-full"/>
        </n-form-item>

        <n-form-item label="Voltage Gain" path="voltageGain">
            <n-input-number v-model:value="model.voltageGain" class="w-full"/>
        </n-form-item>

        <n-form-item label="Voltage Offset" path="voltageOffset">
            <n-input-number v-model:value="model.voltageOffset" class="w-full"/>
        </n-form-item>

        <n-form-item>
            <n-button attr-type="submit" type="primary" block>
                Save
            </n-button>
        </n-form-item>
    </n-form>
</template>

<script setup lang="ts">
import type { FormInst, FormRules } from "naive-ui"

const formRef = ref<FormInst>()

const rules = ref<FormRules>({
    sampleRate: {
        required: true
    },
    savingRate: {
        required: true
    },
    currentGain: {
        required: true
    },
    currentOffset: {
        required: true
    },
    voltageGain: {
        required: true
    },
    voltageOffset: {
        required: true
    },
})

const settings = useState<Settings>("settings")

const model = ref<Settings>(settings.value)

function onSubmit() {
    formRef.value?.validate((errors) => {
        if (!errors) {
            settings.value = model.value
            saveFile(JSON.stringify(model.value), "settings.json", "application/json")
        }
    })
}
</script>