<template>
    <div>
        <naive-navbar>
            <template #start>
                <NuxtLink to="/" class="flex items-center gap-3">
                    <NaiveIcon name="ph:activity" :size="25"></NaiveIcon>
                    <n-text strong>Battery Energy Monitor</n-text>
                </NuxtLink>
            </template>

            <template #end>
                <NaiveColorModeSwitch />
            </template>
        </naive-navbar>
    </div>
</template>

<script setup lang="ts">
</script>