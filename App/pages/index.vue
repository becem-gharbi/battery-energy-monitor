<template>
    <div>
        <DataSelect v-if="!settings" />

        <div v-else>
            <ul>
                <n-select v-model:value="currentSessionSelect" :options="sessionsSelect" />
            </ul>

            <ChartMeasurements :measurements="measurements" />
        </div>
    </div>
</template>

<script setup lang="ts">
import type { SelectOption } from "naive-ui"

const sessions = useState<Session[]>("sessions")
const settings = useState<Settings>("settings")
const currentSession = ref<Session>()
const measurements = ref<Measurements>()

const sessionsSelect = computed<SelectOption[]>(() => sessions.value.map(el => ({
    label: el.name,
    value: el.lastModified
})))

const currentSessionSelect = ref()

watch(sessions, () => {
    if (sessions.value?.length > 0) {
        currentSession.value = sessions.value[0]
        currentSessionSelect.value = currentSession.value?.lastModified
    }
})

watch(currentSessionSelect, () => {
    currentSession.value = sessions.value.find(el => el.lastModified === currentSessionSelect.value)
})

watch(currentSession, async () => {
    if (currentSession.value) {
        measurements.value = await transformSession(currentSession.value)
    }
})
</script>